/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 12:04:36 by kalhanaw          #+#    #+#             */
/*   Uparse_sessionated: 2026/02/03 11:27:55 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "parse.h"
#include <fcntl.h>

static int	check_path(const char *s)
{
	size_t	l;

	l = ft_strlen(s);
	if (l < 5 || ft_strncmp(&s[l - 4], ".cub", 4))
		return (0);
	return (1);
}

static void	init_parse_session(t_parse_session *parse_session, t_init_data *init_data, t_mapbuf *mb)
{
	ft_bzero(init_data, sizeof(*init_data));
	ft_bzero(mb, sizeof(*mb));
	init_data->map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!init_data->map)
		exit_text("Error\nMalloc failed\n");
	parse_session->data = init_data;
	parse_session->map_buffer = mb;
	parse_session->fd = -1;
	parse_session->line = NULL;
}

static void	read_loop(t_parse_session *parse_session, int *in_map)
{
	parse_session->line = get_next_line(parse_session->fd);
	while (parse_session->line)
	{
		parse_line(parse_session, parse_session->line, in_map);
		free(parse_session->line);
		parse_session->line = get_next_line(parse_session->fd);
	}
}

void	parse_input(t_init_data *init_data, char *path)
{
	t_parse_session	parse_session;
	int				in_map;
	t_mapbuf		map_buffer;

	if (!init_data || !path || !check_path(path))
		exit_text("Error\nWrong file\n");
	init_parse_session(&parse_session, init_data, &map_buffer);
	in_map = 0;
	parse_session.fd = open(path, O_RDONLY);
	if (parse_session.fd < 0)
		exit_parse(&parse_session, "Error\nWrong file\n");
	read_loop(&parse_session, &in_map);
	close(parse_session.fd);
	parse_session.fd = -1;
	if (!in_map)
		exit_parse(&parse_session, "Error\nMissing map\n");
	build_map(&parse_session);
	find_player(&parse_session);
}
