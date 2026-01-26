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
#include "parse.h"
#include <fcntl.h>

static int check_path(const char *s)
{
	size_t l;

	l = ft_strlen(s);
	if (l < 5 || ft_strncmp(&s[l - 4], ".cub", 4))
		return (0);
	return (1);
}

static void	init_parse_data(t_parse_data *pd, t_init_data *data, t_mapbuf *mb)
{
	ft_bzero(data, sizeof(*data));
	ft_bzero(mb, sizeof(*mb));
	pd->data = data;
	pd->mb = mb;
	pd->fd = -1;
	pd->line = NULL;
}

void	parse_input(t_init_data *data, char *path)
{
	t_parse_data	pdata;
	int			in_map;
	t_mapbuf	mb;

	if (!data || !path || !check_path(path))
		exit_text("Error\nWrong file\n");
	init_parse_data(&pdata, data, &mb);
	in_map = 0;
	pdata.fd = open(path, O_RDONLY);
	if (pdata.fd < 0)
		exit_parse(&pdata, "Error\nWrong file\n");
	while ((pdata.line = get_next_line(pdata.fd)))
	{
		parse_line(&pdata, pdata.line, &in_map);
		free(pdata.line);
		pdata.line = NULL;
	}
	close(pdata.fd);
	pdata.fd = -1;
	if (!in_map)
		exit_parse(&pdata, "Error\nMissing map\n");
	build_map(&pdata);
	find_player(&pdata);
}
