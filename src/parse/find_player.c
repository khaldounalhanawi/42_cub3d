/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 12:04:36 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/19 16:05:06 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "main.h"
#include <fcntl.h>

static int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	handle_player_cell(t_init_data *d, t_map *m, 
		int x, int y, int *count)
{
	char	c;

	c = m->grid[y][x];
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		d->player_x = x;
		d->player_y = y;
		d->player_dir = c;
		m->grid[y][x] = '0';
		(*count)++;
	}
}

void	find_player(t_init_data *d, t_map *m)
{
	int	x;
	int	y;
	int	count;

	count = 0;
	y = 0;
	while (y < m->height)
	{
		x = 0;
		while (x < m->width)
		{
			handle_player_cell(d, m, x, y, &count);
			x++;
		}
		y++;
	}
	if (count != 1)
		exit_text("Error\nInvalid player count\n");
}
