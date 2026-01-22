/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/21 17:16:39 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "main.h"
#include "mlx.h"
#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>

int	close_window(t_game *game)
{
	printf ("Thank you for playing!\n");
	clean_system_exit (game, FULL, NULL);
	return (1);
}

int	hook_keyboard(int keycode, t_game *game)
{
	if (keycode == 53)
		close_window (game);
	return (1);
}

void	my_mlx_pixel_put(t_image *frame, t_player a, int color)
{
	char	*target;

	if (a.pos_x > WIDTH || a.pos_y > HEIGHT || a.pos_x < 0 || a.pos_y < 0)
		return ;
	target = (char *)frame->addr + ((int)a.pos_y * (frame->line_length) + (int)a.pos_x
			* (frame->bpp / 8));
	*(int *)target = color;
}

int	update_and_render(t_game *game)
{
	// printf ("player stats: (%f,%f)\n", game->player.pos_x, game->player.pos_y);
	my_mlx_pixel_put (&game->frame, game->player, 0xff00ff);
	mlx_put_image_to_window (game->mlx, game->win, game->frame.img, 0, 0);
	return (0);
}

void	set_hooks(t_game *game)
{
	mlx_key_hook(game->win, hook_keyboard, game);
	mlx_hook(game->win, 17, 0L, close_window, game);
	mlx_loop_hook (game->mlx, update_and_render, game);
}

int main(int argc, char **argv)
{
	(void) argv; // TEMP
	(void) argc; // TEMP
	t_game		game;
	t_init_data data;

	data = example_data (); // TEMP
	// if (argc != 2)
	// 	exit_text ("Wrong count of arguments\n");
	// parse_input (&data, argv[1]);
	// validate_input (game);
	init_system (&game, data);
	clear_data (data);
	set_hooks (&game);
	// mlx_put_image_to_window (game.mlx, game.win, game.textures[north].img, 0, 0); // TEMP
	mlx_loop (game.mlx);
	clean_system_exit (&game, FULL, NULL);
	return (0);
}
