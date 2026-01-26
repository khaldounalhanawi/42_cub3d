#ifndef VALIDATING_H
# define VALIDATING_H

#include "libft.h"
#include "data_types.h"
#include <stdlib.h>
#include <unistd.h>

void	validate_input(t_init_data *data);
void	exit_validate(t_init_data *data, char *msg);
void	free_visited(t_init_data *data, char **visited);
void	exit_map_error(t_init_data *data, char **visited);

#endif
