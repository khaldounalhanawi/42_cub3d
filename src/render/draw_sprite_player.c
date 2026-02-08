/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite_player.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/02/08 12:18:43 by kalhanaw         ###   ########.fr       */
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
	int		x;
	int		y;
	int		screen_pos_x;
	int		screen_pos_y;
	double	offset;
	int		color;
	t_image	*sprite;

	sprite = &game->textures[sprite_player];
	if (game->input.backward || game->input.forward)
		offset = fabs((sin(get_time() * 4.0) * 1.0) * 20);
	else
		offset = fabs((sin(get_time()) * 0.8) * 30);
	screen_pos_x = WIDTH / 2 - (sprite->width / 2);
	screen_pos_y = HEIGHT - sprite->height + (int)offset;
	y = -1;
	while (++y < sprite->height && screen_pos_y + y < HEIGHT)
	{
		if (screen_pos_y + y < 0)
			continue ;
		x = -1;
		while (++x < sprite->width && screen_pos_x + x < WIDTH)
		{
			if (screen_pos_x + x < 0)
				continue ;
			color = sprite->addr[y * sprite->width + x];
			if ((color & 0x00FFFFFF) != 0)
				game->frame.addr[(screen_pos_y + y) * WIDTH
					+ (screen_pos_x + x)] = color;
		}
	}
}
