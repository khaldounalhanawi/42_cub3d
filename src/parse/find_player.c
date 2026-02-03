/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 12:04:36 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/02/03 11:15:57 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <fcntl.h>

static void	handle_player_cell(t_init_data *data, int x, int y, int *count)
{
	char	c;

	c = data->map->grid[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		data->player_x = x;
		data->player_y = y;
		data->player_dir = c;
		data->map->grid[y][x] = '0';
		(*count)++;
	}
}

void	find_player(t_temp_parse *pdata)
{
	int			x;
	int			y;
	int			count;
	t_init_data	*data;

	data = pdata->data;
	count = 0;
	y = 0;
	while (y < data->map->height)
	{
		x = 0;
		while (x < data->map->width)
		{
			handle_player_cell(data, x, y, &count);
			x++;
		}
		y++;
	}
	if (count != 1)
		exit_parse(pdata, "Error\nInvalid player count\n");
}
