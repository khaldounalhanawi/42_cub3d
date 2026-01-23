/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
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

static int check_path(const char *s)
{
	size_t l;

	l = ft_strlen(s);
	if (l < 5 || ft_strncmp(&s[l - 4], ".cub", 4))
		return (0);
	return (1);
}

void	parse_input(t_init_data *data, char *path)
{
	int			fd;
	char		*line;
	int			in_map;
	t_mapbuf	mb;

	line = NULL;
	in_map = 0;
	if (!data || !path || !check_path(path))
		exit_text("Wrong file\n");
	ft_bzero(data, sizeof(*data));
	ft_bzero(&mb, sizeof(mb));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		exit_text("Wrong file\n");
	while ((line = get_next_line(fd)))
	{
		parse_line(data, &mb, line, &in_map);
		free(line);
	}
	close(fd);
	if (!in_map)
		exit_text("Missing map\n");
	finalize_parse(data, &mb);
	// try to make all the important functions clear in the body,
	
}
