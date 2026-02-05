/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_player.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/02/01 13:04:11 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "mlx.h"
#include <math.h>
#include <sys/time.h>
#include <stdlib.h>

double	get_time(void)
{
	struct timeval	tp;
	double			ret;

	gettimeofday (&tp, NULL);
	ret = tp.tv_sec + (tp.tv_usec / 1000000.0);
	return (ret);
}

void	draw_player_sprite(t_game *game)
{
	int		screen_pos_x;
	int		screen_pos_y;
	double	offset;

	if (game->input.backward || game->input.forward)
		offset = fabs((sin(get_time () * 4.0) * 1.0) * 20);
	else
		offset = fabs((sin(get_time ()) * 0.8) * 30);
	screen_pos_x = WIDTH / 2 - (game->textures[sprite_player].width / 2);
	screen_pos_y = HEIGHT - (game->textures[sprite_player].height);
	mlx_put_image_to_window (game->mlx, game->win,
		game->textures[sprite_player].img,
		screen_pos_x, screen_pos_y + (int)offset);
}
