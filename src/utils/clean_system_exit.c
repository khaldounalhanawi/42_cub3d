/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_system_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:18:22 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/20 18:16:30 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_utils.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>

static void	clear_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	i = -1;
	if (map->grid)
	{
		while (++i < map->height)
			free (map->grid[i]);
		free (map->grid);
	}
}

void	clear_data(t_init_data data)
{
	if (data.north_tex)
		free (data.north_tex);
	if (data.south_tex)
		free (data.south_tex);
	if (data.east_tex)
		free (data.east_tex);
	if (data.west_tex)
		free (data.west_tex);
	if (data.map)
	{
		clear_map (data.map);
		free (data.map);
	}
}

void	clear_data_exit(t_init_data data, char *msg)
{
	if (data.north_tex)
		free (data.north_tex);
	if (data.south_tex)
		free (data.south_tex);
	if (data.east_tex)
		free (data.east_tex);
	if (data.west_tex)
		free (data.west_tex);
	if (data.map)
	{
		clear_map (data.map);
		free (data.map);
	}
	ft_putstr_fd (msg, 2);
	exit (1);
}

static void	clear_images(t_game *game)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (game->textures[i].img)
			mlx_destroy_image (game->mlx, game->textures[i].img);
	}
}

//	for linux mlx_destroy_display(game->mlx) ??
void	clean_system_exit(t_game *game, int code, char *msg)
{
	if (code >= IMAGES)
		clear_images (game);
	if (code >= FULL)
	{
		mlx_destroy_image (game->mlx, game->frame.img);
		mlx_destroy_window (game->mlx, game->win);
		clear_map (game->map);
	}
	if (msg)
		ft_putstr_fd (msg, 2);
	exit (0);
}
