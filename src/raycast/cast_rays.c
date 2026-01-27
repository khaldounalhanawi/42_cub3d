/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/27 16:37:19 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include "main.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

enum
{
	X,
	Y
};

void	set_initial_step(t_raycast *ray, double pos_x, double pos_y)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (pos_x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - pos_x) * ray->delta_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (pos_y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - pos_y) * ray->delta_y;
	}
}

void	loop_dda(t_raycast *ray, t_map map)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = X;
		}
		else
		{
			ray->side_dist_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = Y;
		}
		if (ray->map_x < 0 || ray->map_y < 0
			|| ray->map_x >= map.width || ray->map_y >= map.height)
			ray->hit = 1;
		else if (map.grid[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

double	calculate_distance(t_game *game, t_raycast *ray, int x)
{
	double	camera_x;
	double	distance;
	double	pos_x;
	double	pos_y;

	camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
	pos_x = game->player.pos_x / UNIT_SIZE;
	pos_y = game->player.pos_y / UNIT_SIZE;
	ray->map_x = (int)pos_x;
	ray->map_y = (int)pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1 / ray->ray_dir_y);
	set_initial_step(ray, pos_x, pos_y);
	loop_dda(ray, *game->map);
	if (ray->side == X)
		distance = fabs((ray->map_x - pos_x
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x);
	else
		distance = fabs((ray->map_y - pos_y
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y);
	return (distance);
}


void	calculate_draw_start_end(t_rayhit_info *ray_info)
{
	int	line_height;

	line_height = (int)(HEIGHT / ray_info->distance);
	ray_info->draw_start = -line_height / 2 + HEIGHT / 2;
	if (ray_info->draw_start < 0)
		ray_info->draw_start = 0;
	ray_info->draw_end = line_height / 2 + HEIGHT / 2;
	if (ray_info->draw_end >= HEIGHT)
		ray_info->draw_end = HEIGHT - 1;
}

void	set_wall_side(t_rayhit_info *ray_info, t_raycast ray)
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

void	get_position_on_texture(double pos_x, double pos_y,
		t_raycast ray, t_rayhit_info *ray_info)
{
	double	wall_x;

	if (ray.side == X)
		wall_x = pos_y + ray_info->distance * ray.ray_dir_y;
	else
		wall_x = pos_x + ray_info->distance * ray.ray_dir_x;
	wall_x -= floor(wall_x);
	ray_info->texture_x_pos = wall_x * TEXTURE_DIM;
	if ((ray.side == X && ray.ray_dir_x < 0)
		|| (ray.side == Y && ray.ray_dir_y > 0))
		ray_info->texture_x_pos = TEXTURE_DIM - ray_info->texture_x_pos - 1;
}

t_rayhit_info	create_ray_hit(t_game *game, int x)
{
	t_rayhit_info	ray_info;
	t_raycast		ray;
	double			pos_x;
	double			pos_y;
	
	pos_x = game->player.pos_x / UNIT_SIZE;
	pos_y = game->player.pos_y / UNIT_SIZE;
	ray_info.distance = calculate_distance (game, &ray, x);
	calculate_draw_start_end (&ray_info);
	set_wall_side (&ray_info, ray);
	get_position_on_texture (pos_x, pos_y, ray, &ray_info);
	return (ray_info);
}

void	cast_rays (t_game *game)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		game->ray_hits[x] = create_ray_hit (game, x);
		x ++;
	}
}