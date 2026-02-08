/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_II.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/23 17:35:15 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "local_hooks.h"
#include <math.h>

void	rot_right(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = (old_dir_x * cos (ROTATION))
		- (game->player.dir_y * sin(ROTATION));
	game->player.dir_y = (old_dir_x * sin (ROTATION))
		+ (game->player.dir_y * cos (ROTATION));
	game->player.plane_x = (old_plane_x * cos (ROTATION))
		- (game->player.plane_y * sin(ROTATION));
	game->player.plane_y = (old_plane_x * sin (ROTATION))
		+ (game->player.plane_y * cos (ROTATION));
}

void	rot_left(t_game *game)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = (old_dir_x * cos (-ROTATION))
		- (game->player.dir_y * sin(-ROTATION));
	game->player.dir_y = (old_dir_x * sin (-ROTATION))
		+ (game->player.dir_y * cos (-ROTATION));
	game->player.plane_x = (old_plane_x * cos (-ROTATION))
		- (game->player.plane_y * sin(-ROTATION));
	game->player.plane_y = (old_plane_x * sin (-ROTATION))
		+ (game->player.plane_y * cos (-ROTATION));
}
