/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/02/01 13:00:56 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "local_hooks.h"
#include "ray_caster.h"
#include "render.h"
#include "mlx.h"

#include <stdlib.h>
#include <math.h>

#include <sys/time.h>
#include <math.h>

void test_render(t_game *game)
{
	int		x;
	int		y;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		color;
	double	distance;
	double	alpha;
	int		fog_color;
	int		frame_color;
	int		r;
	int		g;
	int		b;

	x = 0;
	while (x < game->screen_width)
	{
		y = 0;
		while (y < game->ray_hits[x].draw_start)
		{
			game->frame.addr[y * (game->frame.line_length / 4) + x] = game->ceiling_color;
			y++;
		}
		tex_x = (int)game->ray_hits[x].texture_x_pos;
		if (tex_x < 0)
			tex_x = 0;
		if (tex_x >= TEXTURE_DIM)
			tex_x = TEXTURE_DIM - 1;
		step = (double)TEXTURE_DIM / game->ray_hits[x].line_height;
		tex_pos = (game->ray_hits[x].draw_start - game->screen_height / 2 + game->ray_hits[x].line_height / 2) * step;
		y = game->ray_hits[x].draw_start;
		distance = game->ray_hits[x].distance;
		alpha = (distance - 0.5) / (15.0 - 0.5);
		if (alpha < 0)
			alpha = 0;
		if (alpha > 0.8)
			alpha = 0.8;
		fog_color = 0x6B4466;
		while (y <= game->ray_hits[x].draw_end)
		{
			tex_y = (int)tex_pos;
			if (tex_y >= TEXTURE_DIM)
				tex_y = TEXTURE_DIM - 1;
			tex_pos += step;
			color = game->textures[game->ray_hits[x].wall_side].addr[tex_y * TEXTURE_DIM + tex_x];
			frame_color = color;
			r = (int)(((frame_color >> 16) & 0xFF) * (1 - alpha) + ((fog_color >> 16) & 0xFF) * alpha);
			g = (int)(((frame_color >> 8) & 0xFF) * (1 - alpha) + ((fog_color >> 8) & 0xFF) * alpha);
			b = (int)((frame_color & 0xFF) * (1 - alpha) + (fog_color & 0xFF) * alpha);
			color = (r << 16) | (g << 8) | b;
			game->frame.addr[y * (game->frame.line_length / 4) + x] = color;
			y++;
		}
		
		// Draw floor as solid color
		y = game->ray_hits[x].draw_end + 1;
		while (y < game->screen_height)
		{
			game->frame.addr[y * (game->frame.line_length / 4) + x] = game->floor_color;
			y++;
		}
		x++;
	}
	
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
}

int	update_and_render(t_game *game)
{
	update_position (game);
	cast_rays (game);
	test_render (game);
	draw_player_sprite (game);
	draw_minimap (game);
	return (0);
}

void	set_hooks(t_game *game)
{
	mlx_hook (game->win, 17, 0L, close_window, game);
	mlx_hook (game->win, 2, 1L << 0, key_press, game);
	mlx_hook (game->win, 3, 1L << 1, key_release, game);
	mlx_loop_hook (game->mlx, update_and_render, game);
}
