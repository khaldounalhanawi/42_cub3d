/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_parse.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 13:58:04 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/02/03 13:58:49 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCAL_PARSE_H
# define LOCAL_PARSE_H
# include "data_types.h"

void	parse_input(t_init_data *data, char *path);
int		check_line(char *line, int in_map);
void	exit_text(char *msg);
void	parse_line(t_parse_session *pdata, char *line, int *in_map);
void	build_map(t_parse_session *pdata);
void	find_player(t_parse_session *pdata);

void	set_texture(t_parse_session *pdata, char **dst, char *raw);
void	set_color(t_parse_session *pdata, int *has_flag, int rgb[3], char *raw);

void	free_map(t_map *m);
void	free_init_data(t_init_data *d);
void	free_mapbuf(t_mapbuf *mb);

void	exit_parse(t_parse_session *pdata, char *msg);

void	exit_validate(t_init_data *data, char *msg);
void	free_visited(t_init_data *data, char **visited);
void	exit_map_error(t_init_data *data, char **visited);

#endif
