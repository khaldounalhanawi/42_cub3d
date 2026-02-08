/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_utils.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 11:16:39 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/02/08 11:16:36 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCAL_UTILS_H
# define LOCAL_UTILS_H
# include "data_types.h"

// init_player.c
void	init_player(t_game *game, t_init_data data);

// clean_system_exit.c
void	clear_data(t_init_data data);
void	clear_data_exit(t_init_data data, char *msg);
void	clean_system_exit(t_game *game, int code, char *msg);

// init_images.c
void	load_textures(t_game *game, t_init_data data);
t_image	init_frame(void *mlx, int width, int height);

// linux_destroy_display.c
void	destroy_display(void *mlx);

#endif
