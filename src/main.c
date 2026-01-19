/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/19 21:01:14 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "main.h"
#include "mlx.h"
#include <stdio.h> // TEMP

int main(int argc, char **argv)
{
	(void) argv; // TEMP
	(void) argc; // TEMP
	t_game		game;
	t_init_data data;

	// if (argc != 2)
	// 	exit_text ("Wrong count of arguments\n");
	// parse_input (&data, argv[1]);

	data = example_data (); // TEMP
	//printf ("IGNORE THIS MSG %d\n", game.screen_height); // TEMP

	// validate_input (game);
	init_system (&game, data);
	clear_data (data);
	// set_hooks (&game);
	mlx_loop (game.mlx);
	// clean_game (&game);
	return (0);
}
