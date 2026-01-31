/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/30 16:57:27 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "local_hooks.h"

void	update_position(t_game *game)
{
	if (game->input.forward)
		move_forward (game);
	if (game->input.backward)
		move_backward (game);
	if (game->input.left)
		move_left (game);
	if (game->input.right)
		move_right (game);
	if (game->input.rot_left)
		rot_left (game);
	if (game->input.rot_right)
		rot_right (game);
}
