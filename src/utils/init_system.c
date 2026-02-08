/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_system.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:18:22 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/02/08 11:20:27 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_utils.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

static int	convert_arr_to_color(int input[])
{
	return (input[0] << 16 | input[1] << 8 | input[2]);
}

static void	init_input(t_game *game)
{
	game->input.backward = 0;
	game->input.forward = 0;
	game->input.left = 0;
	game->input.right = 0;
	game->input.rot_right = 0;
	game->input.rot_left = 0;
}

static t_mini_map	create_mini_map( t_game *game, int scale)
{
	t_mini_map	mini_map;

	mini_map.scale_factor = scale;
	mini_map.unit = (int)(UNIT_SIZE / scale);
	mini_map.width = mini_map.unit * game->map->width;
	mini_map.height = mini_map.unit * game->map->height;
	mini_map.frame = init_frame (game->mlx, mini_map.width, mini_map.height);
	return (mini_map);
}

void	init_system(t_game *game, t_init_data data)
{
	init_input (game);
	init_player (game, data);
	ft_memset (game->ray_hits, 0, sizeof (game->ray_hits));
	game->floor_color = convert_arr_to_color (data.floor_color);
	game->ceiling_color = convert_arr_to_color (data.ceiling_color);
	game->mlx = mlx_init ();
	if (!game->mlx)
		clear_data_exit (data, "couldn't initiate mlx\n");
	game->win = mlx_new_window (game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->win)
		clear_data_exit (data, "couldn't create window\n");
	load_textures (game, data);
	game->frame = init_frame (game->mlx, WIDTH, HEIGHT);
	if (!game->frame.img)
	{
		clear_data (data);
		clean_system_exit (game, IMAGES, "couldn't initiate frame\n");
	}
	game->map = data.map;
	game->minimap = create_mini_map (game, 4);
	if (!game->minimap.frame.img)
	{
		clear_data (data);
		clean_system_exit (game, FULL, "couldn't create minimap\n");
	}
}
