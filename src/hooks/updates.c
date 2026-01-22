/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/22 19:15:09 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "local_hooks.h"
#include "main.h"
#include "keyboard_keys.h"
#include "mlx.h"
#include <stdio.h>
#include <unistd.h>

void	my_mlx_pixel_put(t_image *frame, t_player a, int color, int arrow_len)
{
	char	*target;

	if (a.pos_x > WIDTH || a.pos_y > HEIGHT || a.pos_x < 0 || a.pos_y < 0)
		return ;
	target = (char *)frame->addr + ((int)a.pos_y * (frame->line_length) + (int)a.pos_x
			* (frame->bpp / 8));
	*(int *)target = color;

	while (arrow_len)
	{
		target = (char *)frame->addr
			+ (int)(a.pos_y + (arrow_len * a.dir_y)) * (frame->line_length)
			+ (int)(a.pos_x + (arrow_len * a.dir_x)) * (frame->bpp / 8);
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
}

void	update_frame(t_game *game)
{
	t_image	new_frame;
	void	*old_image_pointer;

	old_image_pointer = game->frame.img;
	new_frame.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!new_frame.img)
		clean_system_exit (game, FULL, "@update_frame: failed to create a new image\n");
	new_frame.addr = (int*)mlx_get_data_addr(new_frame.img, &new_frame.bpp, 
		&new_frame.line_length, &new_frame.endian);
	if (!new_frame.addr)
		clean_system_exit (game, FULL, "@update_frame: failed to extract addr\n");
	my_mlx_pixel_put (&new_frame, game->player, 0xff00ff, 10);
	game->frame = new_frame;
	mlx_put_image_to_window (game->mlx, game->win, game->frame.img, 0, 0);
	mlx_destroy_image (game->mlx, old_image_pointer);
}
