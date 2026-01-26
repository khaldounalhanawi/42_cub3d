/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_validating.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 12:04:36 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/19 16:05:06 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validating.h"
#include "parse.h"

void	free_visited(t_init_data *data, char **visited)
{
	int	y;

	if (!visited)
		return ;
	y = 0;
	while (y < data->map->height)
		free(visited[y++]);
	free(visited);
}

void	exit_map_error(t_init_data *data, char **visited)
{
	free_visited(data, visited);
	exit_validate(data, "Error\nMap not closed\n");
}

void	exit_validate(t_init_data *data, char *msg)
{
	if (data)
		free_init_data(data);
	exit_text(msg);
}
