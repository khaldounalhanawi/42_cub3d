/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/30 16:44:19 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include <math.h>
#include "local_raycast.h"

static void	calculate_draw_start_end(t_rayhit_info *ray_info)
{
	int	line_height;

	line_height = (int)(HEIGHT / ray_info->distance);
	ray_info->line_height = line_height;
	ray_info->draw_start = -line_height / 2 + HEIGHT / 2;
	if (ray_info->draw_start < 0)
		ray_info->draw_start = 0;
	ray_info->draw_end = line_height / 2 + HEIGHT / 2;
	if (ray_info->draw_end >= HEIGHT)
		ray_info->draw_end = HEIGHT - 1;
}

static void	set_wall_side(t_rayhit_info *ray_info, t_raycast ray)
{
	if (ray.side == X)
	{
		if (ray.ray_dir_x < 0)
			ray_info->wall_side = east;
		else
			ray_info->wall_side = west;
	}
	else
	{
		if (ray.ray_dir_y < 0)
			ray_info->wall_side = south;
		else
			ray_info->wall_side = north;
	}
}

static void	get_position_on_texture(double origin_x, double origin_y,
		t_raycast ray, t_rayhit_info *ray_info)
{
	double	wall_x;

	if (ray.side == X)
		wall_x = origin_y + ray_info->distance * ray.ray_dir_y;
	else
		wall_x = origin_x + ray_info->distance * ray.ray_dir_x;
	wall_x -= floor(wall_x);
	ray_info->texture_x_pos = wall_x * TEXTURE_DIM;
	if ((ray.side == X && ray.ray_dir_x < 0)
		|| (ray.side == Y && ray.ray_dir_y > 0))
		ray_info->texture_x_pos = TEXTURE_DIM - ray_info->texture_x_pos - 1;
}

t_rayhit_info	create_ray_hit(t_player player, t_map map, int x)
{
	t_rayhit_info	ray_info;
	t_raycast		ray;
	double			origin_x;
	double			origin_y;

	ray_info.distance = calculate_distance (player, map, &ray, x);
	calculate_draw_start_end (&ray_info);
	set_wall_side (&ray_info, ray);
	origin_x = player.pos_x / UNIT_SIZE;
	origin_y = player.pos_y / UNIT_SIZE;
	get_position_on_texture (origin_x, origin_y, ray, &ray_info);
	return (ray_info);
}

void	cast_rays(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		game->ray_hits[x] = create_ray_hit (game->player, *game->map, x);
		x ++;
	}
}
