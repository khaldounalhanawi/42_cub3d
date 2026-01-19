/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_system.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:18:22 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/19 19:54:49 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "mlx.h"
#include <stdio.h>

void	set_player_dir(t_game *game, char c)
{
	if (c == 'N')
		{
			game->player.dir_x = 0;
			game->player.dir_y = -1;
		}
	else if (c == 'S')
		{
			game->player.dir_x = 0;
			game->player.dir_y = 1;
		}
	else if (c == 'E')
		{
			game->player.dir_x = 1;
			game->player.dir_y = 0;
		}
	else if (c == 'W')
		{
			game->player.dir_x = -1;
			game->player.dir_y = 0;
		}
}

void	init_player(t_game *game, t_init_data data)
{
	game->player.pos_x = (data.player_x + 0.5) * UNIT_SIZE;
	game->player.pos_y = (data.player_y + 0.5) * UNIT_SIZE;
	set_player_dir (game, data.player_dir);
	game->player.plane_x = -game->player.dir_y * FOV;
	game->player.plane_y =  game->player.dir_x * FOV;
	game->player.move_speed = SPEED;
	game->player.rot_speed = ROTATION;
}

t_image	init_image (t_game *game, char *address)
{
	t_image	image;

	image.img = mlx_xpm_file_to_image (game->mlx, address,
								&image.width, &image.height);
	// if (!image.img)
	//	clean_exit
	image.addr = (int *)mlx_get_data_addr (image.img, &image.bpp,
								&image.line_length, &image.endian);
	return (image);
}

void	load_textures(t_game *game, t_init_data data)
{
	game->textures[0] = init_image (game, data.north_tex);
	game->textures[1] = init_image (game, data.south_tex);
	game->textures[2] = init_image (game, data.east_tex);
	game->textures[3] = init_image (game, data.west_tex);
}

int	convert_arr_to_color(int input[])
{
	return (input[0] << 16 | input[1] << 8 | input[2]);
}

t_image	init_frame(t_game *game)
{
	t_image	frame;

	frame.img = mlx_new_image (game->mlx, game->screen_width, game->screen_height);
	frame.addr = (int *)mlx_get_data_addr (frame.img, &frame.bpp,
				&frame.line_length, &frame.endian);
	frame.width = WIDTH;
	frame.height = HEIGHT;
	return (frame);
}

void	init_system(t_game *game, t_init_data data)
{
	game->screen_height = HEIGHT;
	game->screen_width = WIDTH;
	init_player (game, data);
	game->map = data.map;
	data.map = NULL;
	game->ray_hits = NULL;
	game->mlx = mlx_init ();
	game->win = mlx_new_window (game->mlx, WIDTH, HEIGHT, "cub3D");
	game->floor_color = convert_arr_to_color (data.floor_color);
	game->ceiling_color = convert_arr_to_color (data.ceiling_color);
	load_textures (game, data);
	game->frame = init_frame (game);
	mlx_loop (game->mlx); // TEMP
	
}

/*MLX context & window

Frame buffer image

Texture images loaded into GPU memory

Player vectors (direction & camera plane)

Raycasting buffers

Input state*/