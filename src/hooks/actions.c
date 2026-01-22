/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/22 18:13:36 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "local_hooks.h"
#include "main.h"
#include <unistd.h>
#include <stdio.h>

#define RED "\033[0;31m"
#define RESET "\033[0m"

int	close_window(t_game *game)
{
	write (2, "Thank you for playing!\n", 24);
	clean_system_exit (game, FULL, NULL);
	return (1);
}

void	move_forward(t_game *game)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	new_x = game->player.pos_x + (game->player.dir_x * SPEED);
	new_y = game->player.pos_y + (game->player.dir_y * SPEED);
	map_x = (int) ((new_x / UNIT_SIZE) );
	map_y = (int) ((new_y / UNIT_SIZE) );
	if (map_y < game->map->height && map_x < game->map->width
		&& game->map->grid[map_y][map_x] != '1'
		&& game->map->grid[map_y][map_x] != ' ')
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
	else
		printf (RED "for: hit border at grid[%d][%d] = '%c'\n", map_y, map_x, game->map->grid[map_y][map_x]);
}

void	move_backward(t_game *game)
{
	double	new_x;
	double	new_y;
	int		map_x;
	int		map_y;

	new_x = game->player.pos_x - (game->player.dir_x * SPEED);
	new_y = game->player.pos_y - (game->player.dir_y * SPEED);
	map_x = (int) ((new_x / UNIT_SIZE) );
	map_y = (int) ((new_y / UNIT_SIZE) );
	if (map_y < game->map->height && map_x < game->map->width
		&& game->map->grid[map_y][map_x] != '1'
		&& game->map->grid[map_y][map_x] != ' ')
	{
		game->player.pos_x = new_x;
		game->player.pos_y = new_y;
	}
	else
		printf (RED "back: hit border at grid[%d][%d] = '%c'\n", map_y, map_x, game->map->grid[map_y][map_x]);
}

void	move_left(t_game *game)
{
	double	new_x;
	int		map_x;
	int		map_y;

	new_x = game->player.pos_x - (SPEED);
	map_x = (int) ((new_x / UNIT_SIZE) );
	map_y = (int) ((game->player.pos_y / UNIT_SIZE) );
	if (map_y < game->map->height && map_x < game->map->width
		&& game->map->grid[map_y][map_x] != '1'
		&& game->map->grid[map_y][map_x] != ' ')
	{
		game->player.pos_x = new_x;
	}
	else
		printf (RED "for: hit border at grid[%d][%d] = '%c'\n", map_y, map_x, game->map->grid[map_y][map_x]);
}

void	move_right(t_game *game)
{
	double	new_x;
	int		map_x;
	int		map_y;

	new_x = game->player.pos_x + (SPEED);
	map_x = (int) ((new_x / UNIT_SIZE) );
	map_y = (int) ((game->player.pos_y / UNIT_SIZE) );
	if (map_y < game->map->height && map_x < game->map->width
		&& game->map->grid[map_y][map_x] != '1'
		&& game->map->grid[map_y][map_x] != ' ')
	{
		game->player.pos_x = new_x;
	}
	else
		printf (RED "for: hit border at grid[%d][%d] = '%c'\n", map_y, map_x, game->map->grid[map_y][map_x]);
}