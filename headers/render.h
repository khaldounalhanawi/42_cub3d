/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 14:08:28 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/02/01 13:00:27 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H
# include "data_types.h"

// draw_minimap.c
void	draw_minimap(t_game *game);

// draw_sprite_player.c
void draw_player_sprite(t_game *game);

#endif