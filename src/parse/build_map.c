/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 12:04:36 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/19 16:05:06 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static char	*pad_line(t_parse_data *pd, char *src, int w)
{
	char	*dst;
	int		i;

	dst = (char *)malloc((size_t)w + 1);
	if (!dst)
		exit_parse(pd, "Error\nMalloc failed\n");
	i = 0;
	while (src[i] && src[i] != '\n' && i < w)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < w)
		dst[i++] = ' ';
	dst[w] = '\0';
	return (dst);
}

void	build_map(t_parse_data *pd)
{
	int			i;
	t_init_data	*data;
	t_mapbuf	*mb;

	data = pd->data;
	mb = pd->mb;
	data->map->height = mb->h;
	data->map->width = mb->max_w;
	data->map->grid = (char **)ft_calloc((size_t)data->map->height, sizeof(char *));
	if (!data->map->grid)
    	exit_parse(pd, "Error\nMalloc failed\n");
	i = 0;
	while (i < data->map->height)
	{
		data->map->grid[i] = pad_line(pd, mb->lines[i], data->map->width);
		i++;
	}
	free_mapbuf(mb);
	pd->mb = NULL;
}
