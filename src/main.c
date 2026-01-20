/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/20 13:48:30 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "main.h"
#include "mlx.h"
#include <stdio.h>

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
	// set_hooks (&game);
	mlx_put_image_to_window (game.mlx, game.win, game.textures[north].img, 0, 0); // TEMP
	mlx_loop (game.mlx);
	clean_system_exit (&game, data, 4, NULL);
	return (0);
}
