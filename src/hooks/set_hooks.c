/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/22 15:28:42 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "main.h"
#include "keyboard_keys.h"
#include "mlx.h"
#include <stdio.h>
// #include <stdlib.h>

#include <unistd.h>

int	close_window(t_game *game)
{
	printf ("Thank you for playing!\n");
	clean_system_exit (game, FULL, NULL);
	return (1);
}

int	hook_keyboard(int keycode, t_game *game)
{
	if (keycode == ESC)
		close_window (game);
	return (1);
}

// void	my_mlx_pixel_put(t_image *frame, t_player a, int color)
// {
// 	char	*target;

// 	if (a.pos_x > WIDTH || a.pos_y > HEIGHT || a.pos_x < 0 || a.pos_y < 0)
// 		return ;
// 	target = (char *)frame->addr + ((int)a.pos_y * (frame->line_length) + (int)a.pos_x
// 			* (frame->bpp / 8));
// 	*(int *)target = color;
// }

int	key_press(int key, t_game *game)
{
	if (key == ESC)
		close_window (game);
	if (key == KEY_W)
		game->input.forward = 1;
	if (key == KEY_S)
		game->input.backward = 1;
		return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == KEY_W)
		game->input.forward = 0;
	if (key == KEY_S)
		game->input.backward = 0;
	return (0);
}

void	move_forward(t_game *game)
{
	game->player.pos_y += SPEED;
}

void	move_backward(t_game *game)
{
	game->player.pos_y -= SPEED;
}

void	update_position(t_game *game)
{
	if (game->input.forward)
		move_forward (game);
	if (game->input.backward)
		move_backward (game);
}

int	update_and_render(t_game *game)
{
	t_image	new_frame;
	void *old = game->frame.img;

    new_frame.img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    new_frame.addr = (int*)mlx_get_data_addr(new_frame.img, &new_frame.bpp, 
    &new_frame.line_length, &new_frame.endian);

	update_position (game);
	my_mlx_pixel_put (&new_frame, game->player, 0xff00ff);
	game->frame = new_frame;
	mlx_put_image_to_window (game->mlx, game->win, game->frame.img, 0, 0);
	mlx_destroy_image (game->mlx, old);
	
	return (0);
}

void	set_hooks(t_game *game)
{
	mlx_hook(game->win, 17, 0L, close_window, game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_loop_hook (game->mlx, update_and_render, game);
}

