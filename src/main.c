/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/02/03 13:04:49 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "main.h"
#include "parse.h"
#include "validating.h"
#include <stdio.h>

static void	dump_init_data(t_init_data *data)
{
	int	i;

	printf("\n========== INIT DATA DUMP ==========\n\n");
	printf("Textures:\n");
	printf("  North: %s\n", data->north_tex);
	printf("  South: %s\n", data->south_tex);
	printf("  West:  %s\n", data->west_tex);
	printf("  East:  %s\n", data->east_tex);
	printf("\nColors:\n");
	printf("  Floor:   RGB(%d, %d, %d) [has_floor=%d]\n",
		data->floor_color[0], data->floor_color[1], data->floor_color[2],
		data->has_floor);
	printf("  Ceiling: RGB(%d, %d, %d) [has_ceiling=%d]\n",
		data->ceiling_color[0], data->ceiling_color[1], data->ceiling_color[2],
		data->has_ceiling);
	printf("\nMap:\n");
	printf("  Width:  %d\n", data->map->width);
	printf("  Height: %d\n", data->map->height);
	printf("  Grid:\n");
	i = 0;
	while (i < data->map->height)
	{
		printf("    [%2d] %s\n", i, data->map->grid[i]);
		i++;
	}
	printf("\nPlayer:\n");
	printf("  Position: (%d, %d)\n", data->player_x, data->player_y);
	printf("  Direction: %c\n", data->player_dir);
	printf("\n====================================\n\n");
}

int main(int argc, char **argv)
{
	t_init_data	data;
	t_game		game;

	if (argc != 2)
		exit_text ("Wrong count of arguments\n");
	parse_input (&data, argv[1]);
	validate_input (&data);
	dump_init_data(&data);
	// init_game (&game, data);
	// set_hooks (&game);
	// mlx_loop (game.mlx);
	// cleanup (&game);

	(void)game;
	//(void) argc;
	//(void) argv;
	return (0);
}
