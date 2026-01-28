/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/28 14:03:07 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "local_hooks.h"
#include "ray_caster.h"
#include "mlx.h"

#include <stdlib.h>

void test_render(t_game *game)
{
	int		x;
	int		y;
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		color;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < game->ray_hits[x].draw_start)
		{
			game->frame.addr[y * WIDTH + x] = game->ceiling_color;
			y++;
		}
		tex_x = (int)game->ray_hits[x].texture_x_pos;
		if (tex_x < 0)
			tex_x = 0;
		if (tex_x >= TEXTURE_DIM)
			tex_x = TEXTURE_DIM - 1;
		step = (double)TEXTURE_DIM / game->ray_hits[x].line_height;
		tex_pos = (game->ray_hits[x].draw_start - HEIGHT / 2 + game->ray_hits[x].line_height / 2) * step;
		y = game->ray_hits[x].draw_start;
		while (y <= game->ray_hits[x].draw_end)
		{
			tex_y = (int)tex_pos;
			if (tex_y >= TEXTURE_DIM)
				tex_y = TEXTURE_DIM - 1;
			tex_pos += step;
			color = game->textures[game->ray_hits[x].wall_side].addr[tex_y * TEXTURE_DIM + tex_x];
			game->frame.addr[y * WIDTH + x] = color;
			y++;
		}
		while (y < HEIGHT)
		{
			game->frame.addr[y * WIDTH + x] = game->floor_color;
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->frame.img, 0, 0);
}

int	update_and_render(t_game *game)
{
	update_position (game);
	cast_rays (game);
	// test_render (game);
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
