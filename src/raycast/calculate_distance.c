/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_distance.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 17:29:54 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/30 16:44:41 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_types.h"
#include <math.h>

static void	set_initial_step(t_raycast *ray, double pos_x, double pos_y)
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

static void	loop_dda(t_raycast *ray, t_map map)
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

static void	calculate_ray_direction(t_player player, t_raycast *ray, int x)
{
	double	camera_x;

	camera_x = 2 * (x / (double)WIDTH) - 1;
	ray->ray_dir_x = player.dir_x + player.plane_x * camera_x;
	ray->ray_dir_y = player.dir_y + player.plane_y * camera_x;
}

static void	set_delta_x_y(t_raycast *ray)
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

double	calculate_distance(t_player player, t_map map, t_raycast *ray, int x)
{
	double	distance;
	double	origin_x;
	double	origin_y;

	origin_x = player.pos_x / UNIT_SIZE;
	origin_y = player.pos_y / UNIT_SIZE;
	ray->grid_x = (int)origin_x;
	ray->grid_y = (int)origin_y;
	calculate_ray_direction (player, ray, x);
	set_delta_x_y (ray);
	set_initial_step(ray, origin_x, origin_y);
	loop_dda(ray, map);
	if (ray->side == X)
		distance = fabs((ray->grid_x - origin_x
					+ (1 - ray->step_x) / 2) / ray->ray_dir_x);
	else
		distance = fabs((ray->grid_y - origin_y
					+ (1 - ray->step_y) / 2) / ray->ray_dir_y);
	return (distance);
}
