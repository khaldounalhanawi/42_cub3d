/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/22 18:07:50 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "local_hooks.h"
#include "keyboard_keys.h"

int	key_press(int key, t_game *game)
{
	if (key == ESC)
		close_window (game);
	if (key == KEY_W)
		game->input.forward = 1;
	if (key == KEY_S)
		game->input.backward = 1;
	if (key == KEY_A)
		game->input.left = 1;
	if (key == KEY_D)
		game->input.right = 1;
		return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == KEY_W)
		game->input.forward = 0;
	if (key == KEY_S)
		game->input.backward = 0;
	if (key == KEY_A)
		game->input.left = 0;
	if (key == KEY_D)
		game->input.right = 0;
	return (0);
}

