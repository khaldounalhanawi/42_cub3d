#ifndef PARSE_H
# define PARSE_H
#include "data_types.h"

// parse_input.c
void	parse_input(t_init_data *data, char *path);

// free_utils.c
void	exit_text(char *msg);

// validate_input.c
void	validate_input(t_init_data *data);

#endif
