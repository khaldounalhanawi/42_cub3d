/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 12:04:36 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/02/06 13:01:42 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_TYPES_H
# define DATA_TYPES_H

# ifndef DEBUG
#  define DEBUG 0
# endif
# ifndef WIDTH
#  define WIDTH 1200
# endif
# ifndef HEIGHT
#  define HEIGHT 777
# endif
# ifndef MAP_LIMIT
#  define MAP_LIMIT 100
# endif
# ifndef TEXTURE_DIM
#  define TEXTURE_DIM 1024
# endif
# ifndef UNIT_SIZE
#  define UNIT_SIZE 32
# endif
# ifndef SPEED
#  define SPEED 0.75
# endif
# ifndef ROTATION
#  define ROTATION 0.03
# endif
# ifndef FOV
#  define FOV 0.66
# endif



enum
{
	north,
	south,
	east,
	west,
	sprite_player
};

enum
{
	X,
	Y
};

enum e_cleanup_code
{
	IMAGES = 1,
	FULL
};

typedef struct s_map
{
	int		width;
	int		height;
	char	**grid;
}	t_map;

typedef struct s_mapbuf
{
	char	**lines;
	int		h;
	int		cap;
	int		max_w;
}	t_mapbuf;

typedef struct s_init_data
{
	char	*north_tex;
	char	*south_tex;
	char	*west_tex;
	char	*east_tex;
	int		has_floor;
	int		has_ceiling;
	int		floor_color[3];
	int		ceiling_color[3];
	t_map	*map;
	int		player_x;
	int		player_y;
	char	player_dir;
}	t_init_data;

typedef struct s_parse_session
{
	t_init_data	*data;
	t_mapbuf	*map_buffer;
	int			fd;
	char		*line;
}	t_parse_session;

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
}	t_player;

typedef struct s_raycast
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		grid_x;
	int		grid_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_x;
	double	delta_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
}	t_raycast;

typedef struct s_rayhit_info
{
	double	distance;
	int		wall_side;
	double	texture_x_pos;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_rayhit_info;

typedef struct s_image
{
	void	*img;
	int		*addr;
	int		width;
	int		height;
	int		line_length;
	int		bpp;
	int		endian;
}	t_image;

typedef struct s_input
{
	int	forward;
	int	backward;
	int	right;
	int	left;
	int	rot_right;
	int	rot_left;
}	t_input;

typedef struct s_mini_map
{
	int		unit;
	int		width;
	int		height;
	int		scale_factor;
	t_image	frame;
}	t_mini_map;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_image			frame;
	t_image			textures[5];
	t_rayhit_info	ray_hits[WIDTH];
	t_player		player;
	int				floor_color;
	int				ceiling_color;
	int				screen_width;
	int				screen_height;
	t_map			*map;
	t_input			input;
	t_mini_map		minimap;
}	t_game;

#endif
