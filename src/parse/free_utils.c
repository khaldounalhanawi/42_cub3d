/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 12:04:36 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/19 16:05:06 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include <unistd.h>
#include <stdlib.h>

void	exit_text(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(1);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->grid)
	{
		i = 0;
		while (i < map->height)
		{
			free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	free(map);
}

void	free_init_data(t_init_data *data)
{
	if (!data)
		return ;
	free(data->north_tex);
	free(data->south_tex);
	free(data->west_tex);
	free(data->east_tex);
	data->north_tex = NULL;
	data->south_tex = NULL;
	data->west_tex = NULL;
	data->east_tex = NULL;
	free_map(data->map);
	data->map = NULL;
}

void	free_mapbuf(t_mapbuf *mb)
{
	int	i;

	if (!mb || !mb->lines)
		return ;
	i = 0;
	while (i < mb->h)
	{
		free(mb->lines[i]);
		i++;
	}
	free(mb->lines);
	mb->lines = NULL;
	mb->h = 0;
	mb->cap = 0;
	mb->max_w = 0;
}

void	exit_parse(t_parse_data *pdata, char *msg)
{
	if (pdata)
	{
		if (pdata->line)
		{
			free(pdata->line);
			pdata->line = NULL;
		}
		if (pdata->fd >= 0)
		{
			close(pdata->fd);
			pdata->fd = -1;
		}
		if (pdata->mb)
			free_mapbuf(pdata->mb);
		if (pdata->data)
			free_init_data(pdata->data);
	}
	exit_text(msg);
}
