/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/02/03 15:18:36 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "main.h"
#include "parse.h"
#include "mlx.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	t_game		game;
	t_init_data data;

	if (argc != 2)
		exit_text ("Wrong count of arguments\n");
	parse_file (&data, argv[1]);
	validate_data (&data);
	init_system (&game, data);
	data.map = NULL;
	clear_data (data);
	set_hooks (&game);
	mlx_loop (game.mlx);
	clean_system_exit (&game, FULL, NULL);
	return (0);
}
