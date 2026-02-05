# Linux Rendering Issues - Fix Documentation

## Date
February 5, 2026

## Issues Identified

### 1. Minimap Flickering on Linux

**Problem:**
The minimap was flickering on Linux but not on Mac.

**Root Cause:**
In `src/render/draw_minimap.c`, the `draw_minimap()` function was calling `mlx_new_image()` every single frame (60+ times per second) inside `create_mini_map()`. On Linux X11, image allocation is significantly slower than on Mac's graphics system, causing visible flickering.

**Original Code:**
```c
void	draw_minimap(t_game *game)
{
	t_image		new_frame;
	t_mini_map	mini_map;
	int			padding;

	padding = 10;
	mini_map = create_mini_map (game, &new_frame, 3);  // Creates new image every frame!
	fill_background (mini_map.frame, mini_map.unit, 0x99006666);
	draw_walls (mini_map.frame, *game->map, mini_map.unit, 0x22936075);
	draw_player (game, mini_map, 0xFF2200);
	mlx_put_image_to_window (game->mlx, game->win, mini_map.frame->img,
		WIDTH - mini_map.width - padding, HEIGHT - mini_map.height - padding);
	mlx_destroy_image (game->mlx, mini_map.frame->img);  // Destroyed immediately after display
}
```

**Solution:**
Use a static variable to cache the minimap image and reuse it every frame, similar to how `game->frame` is reused for the main 3D rendering.

**Fixed Code:**
```c
void	draw_minimap(t_game *game)
{
	static t_image	minimap_frame;
	static int		initialized = 0;
	t_mini_map		mini_map;
	int				padding;

	padding = 10;
	if (!initialized)
	{
		mini_map = create_mini_map (game, &minimap_frame, 3);
		initialized = 1;
	}
	else
	{
		mini_map.scale_factor = 3;
		mini_map.unit = (int)(UNIT_SIZE / mini_map.scale_factor);
		mini_map.width = mini_map.unit * game->map->width;
		mini_map.height = mini_map.unit * game->map->height;
		mini_map.frame = &minimap_frame;
	}
	fill_background (mini_map.frame, mini_map.unit, 0x99006666);
	draw_walls (mini_map.frame, *game->map, mini_map.unit, 0x22936075);
	draw_player (game, mini_map, 0xFF2200);
	mlx_put_image_to_window (game->mlx, game->win, mini_map.frame->img,
		WIDTH - mini_map.width - padding, HEIGHT - mini_map.height - padding);
}
```

**Key Points:**
- Image is created once on first call
- Same image buffer is reused for all subsequent frames
- Pixels are overwritten each frame (this is safe and expected behavior)
- `mlx_put_image_to_window()` copies the data to the window, so modifying pixels afterward doesn't affect the displayed image
- No need to destroy the image every frame

---

### 2. Sprite Transparency Not Working on Linux

**Problem:**
The player sprite had transparency/alpha channel that displayed correctly on Mac but showed a black background on Linux.

**Root Cause:**
XPM transparency handling differs between Mac and Linux. The XPM file defines transparent pixels as `"   c None"` (black/0x000000 in the image data). Mac's graphics system automatically handles this, but Linux X11 does not. Using `mlx_put_image_to_window()` directly displays all pixels including the transparent ones as black.

**Original Code:**
```c
void	draw_player_sprite(t_game *game)
{
	int		screen_pos_x;
	int		screen_pos_y;
	double	offset;

	if (game->input.backward || game->input.forward)
		offset = fabs((sin(get_time () * 4.0) * 1.0) * 20);
	else
		offset = fabs((sin(get_time ()) * 0.8) * 30);
	screen_pos_x = WIDTH / 2 - (game->textures[sprite_player].width / 2);
	screen_pos_y = HEIGHT - (game->textures[sprite_player].height);
	mlx_put_image_to_window (game->mlx, game->win,
		game->textures[sprite_player].img,
		screen_pos_x, screen_pos_y + (int)offset);
}
```

**Solution:**
Manually draw the sprite pixel-by-pixel to `game->frame`, skipping black/transparent pixels.

**Fixed Code:**
```c
void	draw_player_sprite(t_game *game)
{
	int		x;
	int		y;
	int		screen_pos_x;
	int		screen_pos_y;
	double	offset;
	int		color;
	t_image	*sprite;

	sprite = &game->textures[sprite_player];
	if (game->input.backward || game->input.forward)
		offset = fabs((sin(get_time() * 4.0) * 1.0) * 20);
	else
		offset = fabs((sin(get_time()) * 0.8) * 30);
	screen_pos_x = WIDTH / 2 - (sprite->width / 2);
	screen_pos_y = HEIGHT - sprite->height + (int)offset;
	y = -1;
	while (++y < sprite->height && screen_pos_y + y < HEIGHT)
	{
		if (screen_pos_y + y < 0)
			continue;
		x = -1;
		while (++x < sprite->width && screen_pos_x + x < WIDTH)
		{
			if (screen_pos_x + x < 0)
				continue;
			color = sprite->addr[y * sprite->width + x];
			if ((color & 0x00FFFFFF) != 0)  // Skip black/transparent pixels
				game->frame.addr[(screen_pos_y + y) * WIDTH + (screen_pos_x + x)] = color;
		}
	}
}
```

**Key Points:**
- Draw sprite to `game->frame` instead of directly to window
- Check each pixel's color value before drawing
- Skip pixels where `(color & 0x00FFFFFF) == 0` (black/transparent)
- Include bounds checking to prevent drawing outside screen
- Must be called before `mlx_put_image_to_window()` is called for `game->frame`

---

## Technical Explanation

### Why Reusing Images Works

When you call `mlx_put_image_to_window()`, it **copies** the image data to the window's display buffer. It doesn't maintain a live reference to your image. This means:

1. You can safely modify the image pixels after displaying
2. The window continues showing the old frame until you call `mlx_put_image_to_window()` again
3. This is exactly how the main 3D rendering works with `game->frame`

**Rendering Flow:**
```
Frame N:
  1. Clear/draw pixels in image buffer
  2. Call mlx_put_image_to_window() → copies to window
  
Frame N+1:
  1. Overwrite same pixels in image buffer (new data)
  2. Call mlx_put_image_to_window() → copies new data to window
  
... repeat
```

### Why Linux is Different

**Mac (Cocoa/OpenGL):**
- More forgiving graphics pipeline
- Better buffering and optimization
- Automatic transparency handling for XPM
- Faster image allocation

**Linux (X11):**
- Slower image allocation (`mlx_new_image()`)
- No automatic XPM transparency handling
- More sensitive to rapid create/destroy cycles
- Requires explicit pixel manipulation for transparency

---

## Files Modified

1. `src/render/draw_minimap.c` - Fixed flickering by caching minimap image
2. `src/render/draw_sprite_player.c` - Fixed transparency by manual pixel drawing

---

## Testing

After applying these fixes:
- Minimap should render smoothly without flickering on Linux
- Player sprite should display with proper transparency (no black background)
- Performance should be improved due to reduced image allocations
- Both Mac and Linux should display identically
