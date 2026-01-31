/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_draws.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/31 17:23:03 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"

void	draw_square(t_image *frame, double pos[], int width, int color)
{
	int		i;
	int		j;
	char	*target;

	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < width)
		{
			target = (char *)frame->addr
				+ (((int)pos[Y] + i) * frame->line_length)
				+ (((int)pos[X] + j) * frame->bpp / 8);
			*(int *)target = color;
			j ++;
		}
		i ++;
	}
}

void	fill_background(t_image *new_frame, int map_unit, int color)
{
	int		column;
	int		row;
	double	pos[2];

	row = 0;
	while (row * map_unit < new_frame->height)
	{
		column = 0;
		while (column * map_unit < new_frame->width)
		{
			pos[X] = column * map_unit;
			pos[Y] = row * map_unit;
			draw_square (new_frame, pos, map_unit, color);
			column ++;
		}
		row ++;
	}
}
