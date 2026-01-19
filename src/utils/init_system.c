/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_system.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:18:22 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/19 15:56:04 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include <stdio.h>

void	set_player_dir(t_game *game, char c)
{
	if (c == 'N')
		{
			game->player.dir_x = 0;
			game->player.dir_y = -1;
		}
	else if (c == 'S')
		{
			game->player.dir_x = 0;
			game->player.dir_y = 1;
		}
	else if (c == 'E')
		{
			game->player.dir_x = 1;
			game->player.dir_y = 0;
		}
	else if (c == 'W')
		{
			game->player.dir_x = -1;
			game->player.dir_y = 0;
		}
}

void	init_player(t_game *game, t_init_data data)
{
	game->player.pos_x = (data.player_x + 0.5) * UNIT_SIZE;
	game->player.pos_y = (data.player_y + 0.5) * UNIT_SIZE;
	set_player_dir (game, data.player_dir);
	game->player.plane_x = -game->player.dir_y * FOV;
	game->player.plane_y =  game->player.dir_x * FOV;
	game->player.move_speed = SPEED;
	game->player.rot_speed = ROTATION;
}

void	init_system(t_game *game, t_init_data data)
{
	game->screen_height = HEIGHT;
	game->screen_width = WIDTH;
	init_player (game, data);
	game->map = data.map;
	data.map = NULL;
	
	
}

/*MLX context & window

Frame buffer image

Texture images loaded into GPU memory

Player vectors (direction & camera plane)

Raycasting buffers

Input state*/