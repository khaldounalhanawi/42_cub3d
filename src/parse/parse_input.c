/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 13:59:06 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/02/03 15:12:51 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "local_parse.h"
#include "libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static int	check_path(const char *s)
{
	size_t	l;

	l = ft_strlen(s);
	if (l < 5 || ft_strncmp(&s[l - 4], ".cub", 4))
		return (0);
	return (1);
}

static void	init_parse_session(t_parse_session *parse_session,
		t_init_data *data, t_mapbuf *mb)
{
	ft_bzero(data, sizeof(*data));
	ft_bzero(mb, sizeof(*mb));
	data->map = (t_map *)ft_calloc(1, sizeof(t_map));
	if (!data->map)
		exit_text("Error\nMalloc failed\n");
	parse_session->data = data;
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

void	parse_file(t_init_data *data, char *path)
{
	t_parse_session	parse_session;
	int				in_map;
	t_mapbuf		map_buffer;

	if (!data || !path || !check_path(path))
		exit_text("Error\nWrong file\n");
	init_parse_session(&parse_session, data, &map_buffer);
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
