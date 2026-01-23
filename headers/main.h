#ifndef MAIN_H
# define MAIN_H

#include "libft.h"

t_game	example_game (void);
void	parse_input(t_init_data *data, char *path);
int     check_line(char *line, int in_map);
void    exit_text (char *msg);
void	parse_line(t_init_data *data, t_mapbuf *buf, char *line, int *in_map);
void	finalize_parse(t_init_data *data, t_mapbuf *mb);
void	find_player(t_init_data *d, t_map *m);

void    set_texture(char **dst, char *raw);
void    set_color(int *has_flag, int rgb[3], char *raw);

#endif
