/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 14:08:28 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/20 14:08:52 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H

t_init_data	example_data(void); //TEMP
void	init_system(t_game *game, t_init_data data);
void	clear_data(t_init_data data);
void	clean_system_exit(t_game *game, t_init_data data, int code, char *msg);

#endif