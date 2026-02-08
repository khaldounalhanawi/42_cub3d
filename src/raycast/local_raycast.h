/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_raycast.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:35:07 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/30 16:37:48 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCAL_RAYCAST_H
# define LOCAL_RAYCAST_H
# include "data_types.h"

// calculate_distance.c
double	calculate_distance(t_player player, t_map map, t_raycast *ray, int x);

#endif