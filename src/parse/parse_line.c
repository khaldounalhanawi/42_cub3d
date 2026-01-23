/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
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

static void	parse_config_line(t_init_data *data, char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		set_texture(&data->north_tex, line + 3);
	else if (!ft_strncmp(line, "SO ", 3))
		set_texture(&data->south_tex, line + 3);
	else if (!ft_strncmp(line, "WE ", 3))
		set_texture(&data->west_tex, line + 3);
	else if (!ft_strncmp(line, "EA ", 3))
		set_texture(&data->east_tex, line + 3);
	else if (!ft_strncmp(line, "F ", 2))
		set_color(&data->has_floor, data->floor_color, line + 2);
	else if (!ft_strncmp(line, "C ", 2))
		set_color(&data->has_ceiling, data->ceiling_color, line + 2);
	else
		exit_text("Error\nInvalid config\n");
}

static void	grow_mapbuf(t_mapbuf *mapbuff)
{
	char	**new_lines;
	int		new_cap;
	int		i;

	new_cap = mapbuff->cap + 16;
	new_lines = (char **)malloc(sizeof(char *) * new_cap);
	if (!new_lines)
		exit_text("Error\nMalloc failed\n");
	i = 0;
	while (i < mapbuff->h)
	{
		new_lines[i] = mapbuff->lines[i];
		i++;
	}
	free(mapbuff->lines);
	mapbuff->lines = new_lines;
	mapbuff->cap = new_cap;
}

static int	len_nl(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

static void	store_map_line(t_mapbuf *mapbuff, char *line)
{
	int		len;
	char	*dup;

	if (mapbuff->h == mapbuff->cap)
		grow_mapbuf(mapbuff);
	dup = ft_strdup(line);
	if (!dup)   
		exit_text("Error\nMalloc failed\n"); // free shit....mapbuf!
	mapbuff->lines[mapbuff->h] = dup;
	mapbuff->h++;
	len = len_nl(dup);
	if (len > mapbuff->max_w)
		mapbuff->max_w = len;
}

void	parse_line(t_init_data *data, t_mapbuf *buf, char *line, int *in_map)
{
	int	type;

	type = check_line(line, *in_map);
	if (type == 0) //empty
		return ;
	if (type == 2) // config line
	{
		if (*in_map)
			exit_text("Error\nConfig after map\n");
		parse_config_line(data, line);
		return ;
	}
	if (type == 1) // map
	{
		*in_map = 1;
		store_map_line(buf, line);
		return ;
	}
	exit_text("Error\nInvalid line\n");
}


