/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   local_render.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 16:35:07 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/31 16:57:46 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCAL_RENDER_H
# define LOCAL_RENDER_H
# include "data_types.h"

// basic_draws.c
void	draw_square(t_image *frame, double pos[], int width, int color);
void	fill_background(t_image *new_frame, int map_unit, int color);

#endif