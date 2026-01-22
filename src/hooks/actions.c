/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/22 16:12:41 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "local_hooks.h"
#include "main.h"
#include <unistd.h>

int	close_window(t_game *game)
{
	write (2, "Thank you for playing!\n", 24);
	clean_system_exit (game, FULL, NULL);
	return (1);
}

void	move_forward(t_game *game)
{
	game->player.pos_y += SPEED;
}

void	move_backward(t_game *game)
{
	game->player.pos_y -= SPEED;
}

