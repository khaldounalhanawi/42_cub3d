/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/31 13:21:44 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "main.h"
#include "keyboard_keys.h"
#include "mlx.h"
#include <unistd.h>
#include <stdlib.h>

void	draw_player_arrow(t_mini_map map, t_player a, int color, int arrow_len)
{
	char	*target;
	t_image *frame;
	double	scaled_pos_x;
	double	scaled_pos_y;

	frame = map.frame;
	scaled_pos_x = a.pos_x / map.scale_factor;
	scaled_pos_y = a.pos_y / map.scale_factor;
	if (scaled_pos_x > frame->width
		|| scaled_pos_y > frame->height
		|| scaled_pos_x < 0
		|| scaled_pos_y < 0)
		return ;
	target = (char *)frame->addr
		+ ((int)scaled_pos_y * (frame->line_length)
		+ ((int)scaled_pos_x * (frame->bpp / 8)));
	*(int *)target = color;
	while (arrow_len)
	{
		target = (char *)frame->addr
			+ ((int)(scaled_pos_y + (arrow_len * a.dir_y))) * (frame->line_length)
			+ ((int)(scaled_pos_x + (arrow_len * a.dir_x))) * (frame->bpp / 8);
		*(int *)target = color;
		arrow_len --;
	}
}

void	draw_square(t_image *frame, int pos[], int width, int color)
{
	int		i;
	int		j;
	char	*target;

	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < width)
		{
			target = (char *)frame->addr
				+ (int)((pos[Y] + i) * frame->line_length)
				+ (int)((pos[X] + j) * (frame->bpp / 8));
			*(int *)target = color;
			j ++;
		}
		i ++;
	}
}

void	draw_walls(t_image *new_frame, t_map map, int map_unit, int color)
{
	int	column;
	int	row;
	int	pos[2];

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

void	fill_background(t_image *new_frame, int map_unit, int color)
{
	int	column;
	int	row;
	int	pos[2];

	row = 0;
	while (row * map_unit < new_frame->height)
	{
		column = 0;
		while (column * map_unit < new_frame->width)
		{
			pos[X] = column * map_unit;
			pos[Y] = row * map_unit;
			draw_square (new_frame, pos, map_unit, color);
			column ++;
		}
		row ++;
	}
}

t_mini_map	create_mini_map( t_game *game, t_image *frame, int scale)
{
	t_mini_map	mini_map;

	mini_map.scale_factor = scale;
	mini_map.unit = (int)(UNIT_SIZE / mini_map.scale_factor);
	mini_map.width = mini_map.unit * game->map->width;
	mini_map.height = mini_map.unit * game->map->height;
	mini_map.frame = frame;
	mini_map.frame->width = mini_map.width;
	mini_map.frame->height = mini_map.height;
	mini_map.frame->img = mlx_new_image(game->mlx, mini_map.width, mini_map.height);
	if (!mini_map.frame->img)
		clean_system_exit (game, FULL,
			"@create_mini_map: failed to create a new image\n");
	mini_map.frame->addr = (int *) mlx_get_data_addr (mini_map.frame->img, &mini_map.frame->bpp,
			&mini_map.frame->line_length, &mini_map.frame->endian);
	if (!mini_map.frame->addr)
		clean_system_exit (game, FULL,
			"@draw_minimap: failed to extract addr\n");
	return (mini_map);
}

void	draw_player(t_game *game, t_mini_map mini_map, int color)
{
	int	pos[2];

	pos[X] = (game->player.pos_x / UNIT_SIZE * mini_map.unit) - (((int)mini_map.unit / 2) / 2);
	pos[Y] = (game->player.pos_y / UNIT_SIZE * mini_map.unit) - (((int)mini_map.unit / 2) / 2);
	draw_square (mini_map.frame, pos, (int)mini_map.unit / 2, color);
	draw_player_arrow (mini_map, game->player, 0xB88A63, 10);
}
void	draw_minimap(t_game *game)
{
	t_image		new_frame;
	t_mini_map	mini_map;
	int			padding;

	padding = 10;
	mini_map = create_mini_map (game, &new_frame, 2);
	fill_background (mini_map.frame, mini_map.unit, 0x99000200);
	draw_walls (mini_map.frame, *game->map, mini_map.unit, 0x5583AFAF);
	draw_player (game, mini_map, 0xFF0000);
	mlx_put_image_to_window (game->mlx, game->win, mini_map.frame->img,
		WIDTH - mini_map.width - padding, HEIGHT - mini_map.height - padding);
}
