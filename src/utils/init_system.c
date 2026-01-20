/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_system.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:18:22 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/20 13:43:04 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_utils.h"
#include "mlx.h"
#include <stdio.h> // TEMP

void	clean_system_exit(t_game *game, t_init_data data, int code, char *msg);

t_image	init_image (t_game *game, char *address)
{
	t_image	image;

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

	game->textures[north] = init_image (game, data.north_tex);
	game->textures[south] = init_image (game, data.south_tex);
	game->textures[east] = init_image (game, data.east_tex);
	game->textures[west] = init_image (game, data.west_tex);
	i = 0;
	while (i < 4)
	{
		if (!game->textures[i].img)
			clean_system_exit (game, data, 2, "image failed to load\n");
		i ++;
	}
}

int	convert_arr_to_color(int input[])
{
	return (input[0] << 16 | input[1] << 8 | input[2]);
}

t_image	init_frame(t_game *game)
{
	t_image	frame;

	frame.img = mlx_new_image (game->mlx, game->screen_width, game->screen_height);
	if (!frame.img)
		return (frame);
	frame.addr = (int *)mlx_get_data_addr (frame.img, &frame.bpp,
				&frame.line_length, &frame.endian);
	frame.width = WIDTH;
	frame.height = HEIGHT;
	return (frame);
}

void	init_system(t_game *game, t_init_data data)
{
	game->screen_height = HEIGHT;
	game->screen_width = WIDTH;
	init_player (game, data);
	game->map = data.map;
	data.map = NULL;
	game->ray_hits = NULL;
	game->floor_color = convert_arr_to_color (data.floor_color);
	game->ceiling_color = convert_arr_to_color (data.ceiling_color);
	game->mlx = mlx_init ();
	if (!game->mlx)
		clean_system_exit (game, data, 1, "couldn't initiate mlx\n");
	game->win = mlx_new_window (game->mlx, WIDTH, HEIGHT, "cub3D");
	if (!game->win)
		clean_system_exit (game, data, 1, "couldn't create window\n");
	load_textures (game, data);
	game->frame = init_frame (game);
	if (!game->frame.img)
		clean_system_exit (game, data, 2, "couldn't initiate frame\n");
}

#include "libft.h"
#include "stdlib.h"

void	clean_system_exit(t_game *game, t_init_data data, int code, char *msg)
{
	int	i;

	if (code >= 1)
		clear_data (data);
	if (code >= 2)
	{
		i = -1;
		while (++i < 4)
			mlx_destroy_image (game->mlx, game->textures[i].img);
	}
	if (code >= 3)
	{
		mlx_destroy_image (game->mlx, game->frame.img);
		mlx_destroy_window (game->mlx, game->win);
	}
	if (msg)
	{
		ft_putstr_fd (msg, 2);
		exit (1);
	}
	exit (0);
}