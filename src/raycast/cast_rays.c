/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/28 12:53:50 by kalhanaw         ###   ########.fr       */
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
		ray->side_dist_x = (pos_x - ray->grid_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->grid_x + 1.0 - pos_x) * ray->delta_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (pos_y - ray->grid_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->grid_y + 1.0 - pos_y) * ray->delta_y;
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
			ray->grid_x += ray->step_x;
			ray->side = X;
		}
		else
		{
			ray->side_dist_y += ray->delta_y;
			ray->grid_y += ray->step_y;
			ray->side = Y;
		}
		if (ray->grid_x < 0 || ray->grid_y < 0
			|| ray->grid_x >= map.width || ray->grid_y >= map.height)
			ray->hit = 1;
		else if (map.grid[ray->grid_y][ray->grid_x] == '1')
			ray->hit = 1;
	}
}

void	calculate_ray_direction(t_game *game, t_raycast *ray, int x)
{
	double	camera_x;

	camera_x = 2 * (x / (double)WIDTH) - 1;
	ray->ray_dir_x = game->player.dir_x + game->player.plane_x * camera_x;
	ray->ray_dir_y = game->player.dir_y + game->player.plane_y * camera_x;
}

void	set_delta_x_y(t_raycast *ray)
{
	if (ray->ray_dir_x == 0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1 / ray->ray_dir_y);
}

double	calculate_distance(t_game *game, t_raycast *ray, int x)
{
	double	distance;
	double	origin_x;
	double	origin_y;

	origin_x = game->player.pos_x / UNIT_SIZE;
	origin_y = game->player.pos_y / UNIT_SIZE;
	ray->grid_x = (int)origin_x;
	ray->grid_y = (int)origin_y;
	calculate_ray_direction (game, ray, x);
	set_delta_x_y (ray);
	set_initial_step(ray, origin_x, origin_y);
	loop_dda(ray, *game->map);
	if (ray->side == X)
		distance = fabs((ray->grid_x - origin_x
				+ (1 - ray->step_x) / 2) / ray->ray_dir_x);
	else
		distance = fabs((ray->grid_y - origin_y
				+ (1 - ray->step_y) / 2) / ray->ray_dir_y);
	return (distance);
}

void	calculate_draw_start_end(t_rayhit_info *ray_info)
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

void	get_position_on_texture(double origin_x, double origin_y,
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

// t_rayhit_info	create_ray_hit(t_game *game, int x)
// {
// 	t_rayhit_info	ray_info;
// 	t_raycast		ray;
// 	double			pos_x;
// 	double			pos_y;
	
// 	pos_x = game->player.pos_x / UNIT_SIZE;
// 	pos_y = game->player.pos_y / UNIT_SIZE;
// 	ray_info.distance = calculate_distance (game, &ray, x);
// 	calculate_draw_start_end (&ray_info);
// 	set_wall_side (&ray_info, ray);
// 	get_position_on_texture (pos_x, pos_y, ray, &ray_info);
// 	return (ray_info);
// }

// void	cast_rays (t_game *game)
// {
// 	int	x;

// 	x = 0;
// 	while (x < WIDTH)
// 	{
// 		game->ray_hits[x] = create_ray_hit (game, x);
// 		x ++;
// 	}
// }

t_rayhit_info	create_ray_hit(t_game *game, int x)
{
	t_rayhit_info	ray_info;
	t_raycast		ray;
	double			origin_x;
	double			origin_y;
	
	ray_info.distance = calculate_distance (game, &ray, x);
	calculate_draw_start_end (&ray_info);
	set_wall_side (&ray_info, ray);
	origin_x = game->player.pos_x / UNIT_SIZE;
	origin_y = game->player.pos_y / UNIT_SIZE;
	get_position_on_texture (origin_x, origin_y, ray, &ray_info);
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