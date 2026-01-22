/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/22 19:16:38 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "local_hooks.h"
#include "mlx.h"

int	update_and_render(t_game *game)
{
	update_position (game);
	update_frame (game);
	return (0);
}

void	set_hooks(t_game *game)
{
	mlx_hook (game->win, 17, 0L, close_window, game);
	mlx_hook (game->win, 2, 1L << 0, key_press, game);
	mlx_hook (game->win, 3, 1L << 1, key_release, game);
	mlx_loop_hook (game->mlx, update_and_render, game);
}

