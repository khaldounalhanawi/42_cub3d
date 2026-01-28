/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_types.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalhanaw <kalhanaw@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 12:04:36 by kalhanaw          #+#    #+#             */
/*   Updated: 2026/01/28 12:04:55 by kalhanaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DATA_TYPES_H
# define DATA_TYPES_H

# ifndef DEBUG
#  define DEBUG 1
# endif
# ifndef WIDTH
#  define WIDTH 800
# endif
# ifndef HEIGHT
#  define HEIGHT 600
# endif
# ifndef TEXTURE_DIM
#  define TEXTURE_DIM 1024
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

enum
{
	north,
	south,
	east,
	west
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
}	t_init_data;

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
	double	distance;		// distance from player position to a wall
	int		wall_side;		// which side of the wall that the ray hit, to determind NSEW texture to use
	double	texture_x_pos;	// going to be (0..1) * TEXTURE_DIM
	int		line_height;	// the length of the line that needs to be drawn from texture
	int		draw_start;		// start position of drawing of the line
	int		draw_end;		// end position of the line
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

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_image			frame;
	t_image			textures[4];
	t_rayhit_info	ray_hits[WIDTH];
	t_player		player;
	int				floor_color;
	int				ceiling_color;
	int				screen_width;
	int				screen_height;
	t_map			*map;
	t_input			input;
}	t_game;

#endif
