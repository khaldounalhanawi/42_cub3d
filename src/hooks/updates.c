/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/29 18:21:36 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "local_hooks.h"
#include "main.h"
#include "keyboard_keys.h"
#include "mlx.h"
#include <unistd.h>
#include <stdlib.h>

void	my_mlx_pixel_put(t_image *frame, t_player a, int color, int arrow_len)
{
	char	*target;

	if (a.pos_x / 4 > frame->width || a.pos_y / 4 > frame->height || a.pos_x / 4 < 0 || a.pos_y / 4 < 0)
		return ;
	target = (char *)frame->addr
		+ ((int)a.pos_y / 4 * (frame->line_length)
			+ ((int)a.pos_x / 4 * (frame->bpp / 8)));
	*(int *)target = color;
	while (arrow_len)
	{
		target = (char *)frame->addr
			+ ((int)(a.pos_y / 4 + (arrow_len * a.dir_y))) * (frame->line_length)
			+ ((int)(a.pos_x / 4 + (arrow_len * a.dir_x))) * (frame->bpp / 8);
		*(int *)target = color;
		arrow_len --;
	}
}

void	update_position(t_game *game)
{
	if (game->input.forward)
		move_forward (game);
	if (game->input.backward)
		move_backward (game);
	if (game->input.left)
		move_left (game);
	if (game->input.right)
		move_right (game);
	if (game->input.rot_left)
		rot_left (game);
	if (game->input.rot_right)
		rot_right (game);
}

void	draw_square(t_image *frame, int x, int y, int color)
{
	int		i;
	int		j;
	char	*target;

	i = 0;
	while (i < UNIT_SIZE / 4)
	{
		j = 0;
		while (j < UNIT_SIZE / 4)
		{
			target = (char *)frame->addr
				+ ((y + i) * frame->line_length)
				+ ((x + j) * (frame->bpp / 8));
			*(int *)target = color;
			j ++;
		}
		i ++;
	}
}

void	create_walls(t_image *new_frame, t_map map, int map_unit)
{
	int	column;
	int	row;

	row = 0;
	while (row < map.height)
	{
		column = 0;
		while (column < map.width)
		{
			if (map.grid[row][column] == '1'
				&& column * map_unit <= new_frame->width
				&& row * map_unit <= new_frame->height) 
				draw_square (new_frame, column * map_unit, row * map_unit, 0x5583AFAF);
			column ++;
		}
		row ++;
	}
}

void	prefill_background(t_image *new_frame, int map_unit)
{
	int	column;
	int	row;

	row = 0;
	while (row < new_frame->height)
	{
		column = 0;
		while (column < new_frame->width)
		{
			if (column * map_unit <= new_frame->width
				&& row * map_unit <= new_frame->height) 
				draw_square (new_frame, column * map_unit,
					row * map_unit, 0x99000200);
			column ++;
		}
		row ++;
	}
}

t_mini_map	create_mini_map( t_game *game, t_image *frame,int scale)
{
	t_mini_map	mini_map;

	mini_map.scale_factor = scale;
	mini_map.unit = UNIT_SIZE / mini_map.scale_factor;
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
void	draw_minimap(t_game *game)
{
	t_image		*new_frame;
	t_mini_map	mini_map;
	int			padding;

	padding = 10;
	new_frame = malloc (sizeof (t_image));
	mini_map = create_mini_map (game, new_frame, 4);
	prefill_background (mini_map.frame, mini_map.unit);
	create_walls (mini_map.frame, *game->map, mini_map.unit);
	my_mlx_pixel_put (mini_map.frame, game->player, 0xB88A63, 10);
	draw_square (mini_map.frame, game->player.pos_x / 4 - mini_map.unit / 2, game->player.pos_y/ 4 - mini_map.unit / 2, 0xB88A63);
	mlx_put_image_to_window (game->mlx, game->win, mini_map.frame->img,
		WIDTH - mini_map.width - padding, HEIGHT - mini_map.height - padding);
}


