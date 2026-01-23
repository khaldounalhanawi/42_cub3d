/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/23 17:57:07 by kalhanaw         ###   ########.fr       */
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
	// parse_file (&data, argv[1]);
	// validate_data (game);
	init_system (&game, data);
	data.map = NULL;
	clear_data (data);
	set_hooks (&game);
	mlx_loop (game.mlx);
	clean_system_exit (&game, FULL, NULL);
	return (0);
}



	// mlx_put_image_to_window (game.mlx, game.win, game.textures[north].img, 0, 0); // TEMP
