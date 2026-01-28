/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:18:22 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/28 18:18:28 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"

static void	get_player_dir(t_game *game, char c)
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
	get_player_dir (game, data.player_dir);
	game->player.plane_x = -game->player.dir_y * FOV * (game->screen_width / (double)game->screen_height);
	game->player.plane_y = game->player.dir_x * FOV * (game->screen_width / (double)game->screen_height);
	game->player.move_speed = SPEED;
	game->player.rot_speed = ROTATION;
}
