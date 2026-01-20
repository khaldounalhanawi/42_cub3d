/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:16:39 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/20 14:06:59 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCAL_UTILS_H
# define LOCAL_UTILS_H
# include "data_types.h"

// init_player.c
void	init_player(t_game *game, t_init_data data);

// clear_data.c
void	clear_data(t_init_data data);

// clean_system_exit.c
void	clean_system_exit(t_game *game, t_init_data data, int code, char *msg);

#endif
