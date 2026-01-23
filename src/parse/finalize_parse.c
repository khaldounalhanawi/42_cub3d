/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize_parse.c                                   :+:      :+:    :+:   */
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

static void	check_required(t_init_data *d, t_mapbuf *mb)
{
	if (!d->north_tex || !d->south_tex || !d->west_tex || !d->east_tex)
		exit_text("Error\nMissing texture\n");
	if (!d->has_floor || !d->has_ceiling)
		exit_text("Error\nMissing color\n");
	if (!mb->lines || mb->h <= 0 || mb->max_w <= 0)
		exit_text("Error\nEmpty map\n");
}

static char	*pad_line(char *src, int w)
{
	char	*dst;
	int		i;

	dst = (char *)malloc((size_t)w + 1);
	if (!dst)
		exit_text("Error\nMalloc failed\n");
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

static void	free_mapbuf(t_mapbuf *mb)
{
	int	i;

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

static void	build_map(t_init_data *d, t_mapbuf *mb)
{
	int	i;

	d->map = (t_map *)malloc(sizeof(t_map));
	if (!d->map)
		exit_text("Error\nMalloc failed\n");
	d->map->height = mb->h;
	d->map->width = mb->max_w;
	d->map->grid = (char **)malloc(sizeof(char *) * d->map->height);
	if (!d->map->grid)
		exit_text("Error\nMalloc failed\n");
	i = 0;
	while (i < d->map->height)
	{
		d->map->grid[i] = pad_line(mb->lines[i], d->map->width);
		i++;
	}
}

void	finalize_parse(t_init_data *data, t_mapbuf *mb)
{
	check_required(data, mb);
	build_map(data, mb);
	free_mapbuf(mb);
	find_player(data, data->map);
}
