/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:23:47 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/02/03 16:23:53 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "data_types.h"

// parse_input.c
void	parse_file(t_init_data *data, char *path);

// free_utils.c
void	exit_text(char *msg);

// validate_input.c
void	validate_data(t_init_data *data);

#endif
