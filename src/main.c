/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/19 13:31:36 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "main.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	(void) argv; // TEMP
	(void) argc; // TEMP
	t_game		game;
	t_init_data data;

	// if (argc != 2)
	// 	exit_text ("Wrong count of arguments\n");
	// parse_input (&data, argv[1]);

	game = example_game (); // TEMP
	printf ("IGNORE THIS MSG %d\n", game.screen_height); // TEMP

	// validate_input (game);
	init_system (&game, data); // TODO
	// set_hooks (&game);
	// mlx_loop (game.mlx);
	// cleanup (&game);
	return (0);
}
