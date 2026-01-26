#ifndef PARSE_H
# define PARSE_H

#include "libft.h"
#include "data_types.h"
#include <stdlib.h>
#include <unistd.h>

void	parse_input(t_init_data *data, char *path);
int     check_line(char *line, int in_map);
void    exit_text (char *msg);
void	parse_line(t_parse_data *pdata, char *line, int *in_map);
void	build_map(t_parse_data *pdata);
void	find_player(t_parse_data *pdata);

void	set_texture(t_parse_data *pdata, char **dst, char *raw);
void	set_color(t_parse_data *pdata, int *has_flag, int rgb[3], char *raw);

void	free_map(t_map *m);
void	free_init_data(t_init_data *d);
void	free_mapbuf(t_mapbuf *mb);

void	exit_parse(t_parse_data *pdata, char *msg);

#endif
