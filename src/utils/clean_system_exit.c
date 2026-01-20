/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_system_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 12:18:22 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/20 14:04:05 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "local_utils.h"
#include "mlx.h"
#include "libft.h"
#include <stdlib.h>

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
