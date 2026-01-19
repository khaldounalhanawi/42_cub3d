/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 12:04:36 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/19 16:05:06 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_TYPES_H
# define DATA_TYPES_H

# ifndef WIDTH
#  define WIDTH 1920
# endif
# ifndef HEIGHT
#  define HEIGHT 1080
# endif
# ifndef TEXTURE_DIM
#  define TEXTURE_DIM 64
# endif
# ifndef UNIT_SIZE
#  define UNIT_SIZE 32
# endif
# ifndef SPEED
#  define SPEED 3.0
# endif
# ifndef ROTATION
#  define ROTATION 0.03
# endif
# ifndef FOV
#  define FOV 0.66
# endif

typedef struct s_init_data
{
	char	*north_tex;
	char	*south_tex;
	char	*west_tex;
	char	*east_tex;
	int		floor_color[3];
	int		ceiling_color[3];
	t_map	*map;
	int		player_x;
	int		player_y;
	char	player_dir;
} t_init_data;

typedef struct s_map
{
	int		width;
	int		height;
	char	**grid;
} t_map;

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
} t_player;

// raycaster helper, revisit
typedef struct s_raycast
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
} t_raycast;

typedef struct s_rayhit
{
	double	distance;
	int		side;
	int		wall_dir;
	double	wall_hit;
} t_rayhit;

typedef struct s_image
{
	void	*img;
	int		*addr;
	int		width;
	int		height;
	int		line_length;
	int		bpp;
	int		endian;
} t_image;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_player	player;
	t_map		*map;
	t_image		textures[4];
	t_image		frame;
	t_rayhit	*ray_hits;
	int			screen_width; //
	int			screen_height; //
	int			floor_color;
	int			ceiling_color;
} t_game;

#endif

