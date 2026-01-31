/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/23 10:56:59 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/31 18:13:34 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_utils.h"
#include "mlx.h"
#include <stdio.h>

static t_image	init_texture(t_game *game, char *address)
{
	t_image	image;

	image.img = NULL;
	image.addr = NULL;
	image.width = 0;
	image.height = 0;
	image.img = mlx_xpm_file_to_image (game->mlx, address,
			&image.width, &image.height);
	if (!image.img)
		return (image);
	image.addr = (int *)mlx_get_data_addr (image.img, &image.bpp,
			&image.line_length, &image.endian);
	return (image);
}

void	load_textures(t_game *game, t_init_data data)
{
	int	i;

	game->textures[north] = init_texture (game, data.north_tex);
	game->textures[south] = init_texture (game, data.south_tex);
	game->textures[east] = init_texture (game, data.east_tex);
	game->textures[west] = init_texture (game, data.west_tex);
	game->textures[sprite_player] = init_texture (game, "./textures/player_sprite.xpm");
	i = 0;
	while (i < 5)
	{
		if (!game->textures[i].img)
		{
			clear_data (data);
			clean_system_exit (game, IMAGES, "image failed to load\n");
		}
		i ++;
	}
}

t_image	init_frame(t_game *game)
{
	t_image	frame;

	frame.img = NULL;
	frame.addr = NULL;
	frame.img = mlx_new_image (game->mlx,
			game->screen_width, game->screen_height);
	if (!frame.img)
		return (frame);
	frame.addr = (int *)mlx_get_data_addr (frame.img, &frame.bpp,
			&frame.line_length, &frame.endian);
	frame.width = WIDTH;
	frame.height = HEIGHT;
	return (frame);
}
