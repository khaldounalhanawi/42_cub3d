/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/02/08 12:18:52 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "mlx.h"

void	put_pixel(t_image *frame, int x, int y, int color)
{
	frame->addr[y * (frame->line_length / (frame->bpp / 8)) + x] = color;
}

void	draw_floor_ceiling(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->frame.width)
	{
		y = 0;
		while (y < game->frame.height)
		{
			if (y < game->ray_hits[x].draw_start)
				put_pixel (&game->frame, x, y, game->ceiling_color);
			if (y > game->ray_hits[x].draw_end)
				put_pixel (&game->frame, x, y, game->floor_color);
			y ++;
		}
		x ++;
	}
}

void	draw_texture_line(t_image *frame,
		t_rayhit_info ray_info, t_image texture, int x)
{
	int		y;
	int		texture_y;
	int		color;
	double	projected_pos;
	double	step;

	step = (double)TEXTURE_DIM / ray_info.line_height;
	projected_pos = (ray_info.draw_start
			- HEIGHT / 2
			+ ray_info.line_height / 2)
		* step;
	y = ray_info.draw_start;
	while (y <= ray_info.draw_end)
	{
		texture_y = (int)projected_pos;
		if (texture_y < 0)
			texture_y = 0;
		if (texture_y >= TEXTURE_DIM)
			texture_y = TEXTURE_DIM - 1;
		color = texture.addr[texture_y * TEXTURE_DIM
			+ (int)ray_info.texture_x_pos];
		put_pixel (frame, x, y, color);
		projected_pos += step;
		y++;
	}
}

void	draw_3d(t_game *game)
{
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		draw_texture_line (&game->frame,
			game->ray_hits[x],
			game->textures[game->ray_hits[x].wall_side],
			x);
		x++;
	}
	draw_floor_ceiling (game);
}
