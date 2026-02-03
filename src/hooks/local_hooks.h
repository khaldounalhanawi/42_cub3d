/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_hooks.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 16:00:18 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/02/03 17:38:20 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCAL_HOOKS_H
# define LOCAL_HOOKS_H
# include "data_types.h"

enum
{
	LINUX,
	APPLE
};

# ifdef __linux__
#  define SYSTEM LINUX
# elif defined(__APPLE__)
#  define SYSTEM APPLE
# endif

// controls.c
int		key_press(int key, t_game *game);
int		key_release(int key, t_game *game);

// actions_I.c
int		close_window(t_game *game);
void	move_forward(t_game *game);
void	move_backward(t_game *game);
void	move_right(t_game *game);
void	move_left(t_game *game);

// actions_II.c
void	rot_left(t_game *game);
void	rot_right(t_game *game);

// updates.c
void	update_position(t_game *game);

#endif