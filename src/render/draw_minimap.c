/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/02/08 11:32:47 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "main.h"
#include "mlx.h"
#include "local_render.h"

static void	draw_player_arrow(t_mini_map map,
		double pos[], double dir[], int color)
{
	char	*target;
	t_image	frame;
	int		arrow_len;

	frame = map.frame;
	arrow_len = (int)(map.unit / 3 * 2);
	if (pos[X] > frame.width
		|| pos[Y] > frame.height
		|| pos[X] < 0
		|| pos[Y] < 0)
		return ;
	target = (char *)frame.addr
		+ ((int)pos[Y] * (frame.line_length)
			+ ((int)pos[X] * (frame.bpp / 8)));
	*(int *)target = color;
	while (arrow_len)
	{
		target = (char *)frame.addr
			+ ((int)(pos[Y] + (arrow_len * dir[Y]))) * (frame.line_length)
			+ ((int)(pos[X] + (arrow_len * dir[X]))) * (frame.bpp / 8);
		*(int *)target = color;
		arrow_len --;
	}
}

static void	draw_walls(t_image *new_frame, t_map map, int map_unit, int color)
{
	int		column;
	int		row;
	double	pos[2];

	row = 0;
	while (row < map.height)
	{
		column = 0;
		while (column < map.width)
		{
			if (map.grid[row][column]
				&& map.grid[row][column] == '1'
				&& column * map_unit <= new_frame->width
				&& row * map_unit <= new_frame->height)
			{
				pos[X] = column * map_unit;
				pos[Y] = row * map_unit;
				draw_square (new_frame, pos, map_unit, color);
			}
			column ++;
		}
		row ++;
	}
}

static void	draw_player(t_game *game, t_mini_map mini_map, int color)
{
	double	pos[2];
	double	square[2];
	double	dir[2];

	pos[X] = (game->player.pos_x / UNIT_SIZE * mini_map.unit);
	pos[Y] = (game->player.pos_y / UNIT_SIZE * mini_map.unit);
	dir[X] = game->player.dir_x;
	dir[Y] = game->player.dir_y;
	square[X] = pos[X] - ((mini_map.unit / 2) / 2);
	square[Y] = pos[Y] - ((mini_map.unit / 2) / 2);
	draw_square (&(mini_map.frame), square, (int)mini_map.unit / 2, color);
	draw_player_arrow (mini_map, pos, dir, color);
}

void	draw_minimap(t_game *game)
{
	int	padding;

	padding = 10;
	fill_background (&(game->minimap.frame), game->minimap.unit, 0x99006666);
	draw_walls (&(game->minimap.frame), *game->map,
		game->minimap.unit, 0x22936075);
	draw_player (game, game->minimap, 0xFF2200);
	mlx_put_image_to_window (game->mlx, game->win,
		game->minimap.frame.img,
		WIDTH - game->minimap.width - padding,
		HEIGHT - game->minimap.height - padding);
}
