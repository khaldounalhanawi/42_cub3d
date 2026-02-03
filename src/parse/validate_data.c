/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 12:04:36 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/02/03 16:43:00 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_parse.h"
#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

static void	flood_fill(t_init_data *data, char **visited, int x, int y)
{
	if (x < 0 || y < 0 || x >= data->map->width || y >= data->map->height)
		exit_map_error(data, visited);
	if (data->map->grid[y][x] == ' ')
		exit_map_error(data, visited);
	if (visited[y][x])
		return ;
	if (data->map->grid[y][x] != '0')
		return ;
	visited[y][x] = 1;
	flood_fill(data, visited, x + 1, y);
	flood_fill(data, visited, x - 1, y);
	flood_fill(data, visited, x, y + 1);
	flood_fill(data, visited, x, y - 1);
}

static void	check_map_closed(t_init_data *data)
{
	char	**visited;
	int		y;

	visited = (char **)malloc(sizeof(char *) * data->map->height);
	if (!visited)
		exit_validate(data, "Error\nMalloc failed\n");
	y = 0;
	while (y < data->map->height)
	{
		visited[y] = (char *)ft_calloc((size_t)data->map->width, 1);
		if (!visited[y])
		{
			free_visited(data, visited);
			exit_validate(data, "Error\nMalloc failed\n");
		}
		y++;
	}
	flood_fill(data, visited, data->player_x, data->player_y);
	free_visited(data, visited);
}

void	validate_data(t_init_data *data)
{
	if (!data->north_tex || !data->south_tex
		|| !data->west_tex || !data->east_tex)
		exit_validate(data, "Error\nMissing texture\n");
	if (data->map->height > MAP_LIMIT || data->map->width > MAP_LIMIT)
		exit_validate(data, "Error\nMap too large!\n");
	if (!data->has_floor || !data->has_ceiling)
		exit_validate(data, "Error\nMissing color\n");
	if (!data->map || !data->map->grid)
		exit_validate(data, "Error\nEmpty map\n");
	check_map_closed(data);
}
