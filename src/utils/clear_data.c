/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:18:22 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/20 11:51:49 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "data_types.h"
#include <stdlib.h>

void	clear_data(t_init_data data)
{
	int	i;

	if (data.north_tex)
		free (data.north_tex);
	if (data.south_tex)
		free (data.south_tex);
	if (data.east_tex)
		free (data.east_tex);
	if (data.west_tex)
		free (data.west_tex);
	i = -1;
	if (data.map)
	{
		if (data.map->grid)
		{
			while (++i < data.map->height)
				free (data.map->grid[i]);
			free (data.map->grid);
		}
		free (data.map);
	}
}
