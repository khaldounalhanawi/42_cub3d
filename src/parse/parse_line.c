/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 12:04:36 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/02/03 11:28:01 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "parse.h"
#include <fcntl.h>

static void	parse_config_line(t_parse_session *pdata, char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		set_texture(pdata, &pdata->data->north_tex, line + 3);
	else if (!ft_strncmp(line, "SO ", 3))
		set_texture(pdata, &pdata->data->south_tex, line + 3);
	else if (!ft_strncmp(line, "WE ", 3))
		set_texture(pdata, &pdata->data->west_tex, line + 3);
	else if (!ft_strncmp(line, "EA ", 3))
		set_texture(pdata, &pdata->data->east_tex, line + 3);
	else if (!ft_strncmp(line, "F ", 2))
		set_color(pdata, &pdata->data->has_floor,
			pdata->data->floor_color, line + 2);
	else if (!ft_strncmp(line, "C ", 2))
		set_color(pdata, &pdata->data->has_ceiling,
			pdata->data->ceiling_color, line + 2);
	else
		exit_parse(pdata, "Error\nInvalid config\n");
}

static void	grow_mapbuf(t_parse_session *pdata)
{
	char	**new_lines;
	int		new_cap;
	int		i;

	new_cap = pdata->map_buffer->cap + 16;
	new_lines = (char **)malloc(sizeof(char *) * new_cap);
	if (!new_lines)
		exit_parse(pdata, "Error\nMalloc failed\n");
	i = 0;
	while (i < pdata->map_buffer->h)
	{
		new_lines[i] = pdata->map_buffer->lines[i];
		i++;
	}
	free(pdata->map_buffer->lines);
	pdata->map_buffer->lines = new_lines;
	pdata->map_buffer->cap = new_cap;
}

static int	len_nl(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

static void	store_map_line(t_parse_session *pdata)
{
	int		len;
	char	*dup;

	if (pdata->map_buffer->h == pdata->map_buffer->cap)
		grow_mapbuf(pdata);
	dup = ft_strdup(pdata->line);
	if (!dup)
		exit_parse(pdata, "Error\nMalloc failed\n");
	pdata->map_buffer->lines[pdata->map_buffer->h] = dup;
	pdata->map_buffer->h++;
	len = len_nl(dup);
	if (len > pdata->map_buffer->max_w)
		pdata->map_buffer->max_w = len;
}

void	parse_line(t_parse_session *pdata, char *line, int *in_map)
{
	int	type;

	type = check_line(line, *in_map);
	if (type == 0)
		return ;
	if (type == 2)
	{
		if (*in_map)
			exit_parse(pdata, "Error\nConfig after map\n");
		parse_config_line(pdata, line);
		return ;
	}
	if (type == 1)
	{
		*in_map = 1;
		store_map_line(pdata);
		return ;
	}
	exit_parse(pdata, "Error\nInvalid line\n");
}
