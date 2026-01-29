/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/29 14:52:23 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "local_hooks.h"
#include "main.h"
#include "keyboard_keys.h"
#include "mlx.h"
#include <unistd.h>

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

void	create_walls(t_image *new_frame, t_map map)
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
				&& column * UNIT_SIZE / 4 <= new_frame->width
				&& row * UNIT_SIZE / 4 <= new_frame->height) 
				draw_square (new_frame, column * UNIT_SIZE / 4, row * UNIT_SIZE / 4, 0x5583AFAF);
			column ++;
		}
		row ++;
	}
}

void	prefill_background(t_image *new_frame)
{
	int	column;
	int	row;

	row = 0;
	while (row < new_frame->height)
	{
		column = 0;
		while (column < new_frame->width)
		{
			if (column * UNIT_SIZE / 4 <= new_frame->width
				&& row * UNIT_SIZE / 4 <= new_frame->height) 
				draw_square (new_frame, column * UNIT_SIZE / 4, row * UNIT_SIZE / 4, 0x99000200);
			column ++;
		}
		row ++;
	}
}

#include <stdio.h>
#include <stdlib.h>

void	draw_minimap(t_game *game)
{
	t_image	new_frame;
	// int		scale;
	int		on_screen_pos_x;
	int		on_screen_pos_y;

	// scale = 
	// on_screen_pos_x = WIDTH - (int)(WIDTH / 4);
	// on_screen_pos_y = HEIGHT - (int)(HEIGHT / 4);
	on_screen_pos_x = 0;
	on_screen_pos_y = 0;
	new_frame.img = mlx_new_image(game->mlx, UNIT_SIZE / 4 * game->map->width, UNIT_SIZE / 4 * game->map->height);
	if (!new_frame.img)
		clean_system_exit (game, FULL,
			"@draw_minimap: failed to create a new image\n");
	new_frame.addr = (int *) mlx_get_data_addr (new_frame.img, &new_frame.bpp,
			&new_frame.line_length, &new_frame.endian);
	if (!new_frame.addr)
		clean_system_exit (game, FULL,
			"@draw_minimap: failed to extract addr\n");
	new_frame.width = UNIT_SIZE / 4 * game->map->width;
	new_frame.height = UNIT_SIZE / 4 * game->map->height;
	// printf ("dims are  w %d h %d\n", new_frame.width, new_frame.height);
	// exit (0);
	prefill_background (&new_frame);
	create_walls (&new_frame, *game->map);
	my_mlx_pixel_put (&new_frame, game->player, 0xff00ff, 10);
	mlx_put_image_to_window (game->mlx, game->win, new_frame.img, on_screen_pos_x, on_screen_pos_y);
}

// void	update_frame(t_game *game)
// {
// 	t_image	new_frame;
// 	void	*old_image_pointer;

// 	old_image_pointer = game->frame.img;
// 	new_frame.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
// 	if (!new_frame.img)
// 		clean_system_exit (game, FULL,
// 			"@update_frame: failed to create a new image\n");
// 	new_frame.addr = (int *) mlx_get_data_addr (new_frame.img, &new_frame.bpp,
// 			&new_frame.line_length, &new_frame.endian);
// 	if (!new_frame.addr)
// 		clean_system_exit (game, FULL,
// 			"@update_frame: failed to extract addr\n");
// 	create_walls (&new_frame, *game->map);
// 	my_mlx_pixel_put (&new_frame, game->player, 0xff00ff, 10);
// 	game->frame = new_frame;
// 	mlx_put_image_to_window (game->mlx, game->win, game->frame.img, 0, 0);
// 	mlx_destroy_image (game->mlx, old_image_pointer);
// }

