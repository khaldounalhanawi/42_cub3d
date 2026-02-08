/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/02/08 12:17:52 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "local_hooks.h"
#include "ray_caster.h"
#include "render.h"
#include "mlx.h"

int	update_and_render(t_game *game)
{
	update_position (game);
	cast_rays (game);
	draw_3d (game);
	draw_player_sprite (game);
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
	draw_minimap (game);
	return (0);
}

void	set_hooks(t_game *game)
{
	if (SYSTEM == LINUX)
	{
		mlx_hook (game->win, 17, 1L << 17, close_window, game);
		mlx_hook (game->win, 2, 1L << 0, key_press, game);
		mlx_hook (game->win, 3, 1L << 1, key_release, game);
	}
	else if (SYSTEM == APPLE)
	{
		mlx_hook (game->win, 17, 0, close_window, game);
		mlx_hook (game->win, 2, 0, key_press, game);
		mlx_hook (game->win, 3, 0, key_release, game);
	}
	mlx_loop_hook (game->mlx, update_and_render, game);
}
