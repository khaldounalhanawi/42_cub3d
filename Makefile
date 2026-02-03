NAME = cub3D
FLAGS = -Wall -Wextra -Werror -g
INCLUDE_PATH = ./headers
TYPES = data_types.h
LIBRARYS = ./libs
LDFLAGS = -L$(LIBFT_DIR) -lft
INCLUDE_MLX = ./libs/minilibx_opengl_20191021
MLX_L = -L ./libs/minilibx_opengl_20191021 -lmlx -lm -framework OpenGL -framework AppKit

# main
MAIN_DIR = ./src
MAIN_HEADER = $(INCLUDE_PATH)/keyboard_keys.h \
				$(INCLUDE_PATH)/main.h
MAIN_CFILES = $(MAIN_DIR)/main.c
MAIN_OBJS = $(MAIN_CFILES:.c=.o)

# utils
UTILS_DIR = ./src/utils
UTILS_HEADER = ./src/utils/local_utils.h
UTILS_CFILES = 	$(UTILS_DIR)/clean_system_exit.c \
				$(UTILS_DIR)/init_images.c \
				$(UTILS_DIR)/init_player.c \
				$(UTILS_DIR)/init_system.c
UTILS_OBJS = $(UTILS_CFILES:.c=.o)

# raycast
RAYCAST_DIR = ./src/raycast
RAYCAST_HEADER = $(RAYCAST_DIR)/local_raycast.h
RAYCAST_CFILES = $(RAYCAST_DIR)/cast_rays.c \
				 $(RAYCAST_DIR)/calculate_distance.c
RAYCAST_OBJS = $(RAYCAST_CFILES:.c=.o)

# render
RENDER_DIR = ./src/render
RENDER_HEADER = $(RENDER_DIR)/local_render.h
RENDER_CFILES = $(RENDER_DIR)/draw_minimap.c \
				$(RENDER_DIR)/draw_sprite_player.c \
				$(RENDER_DIR)/draw_3d.c \
				$(RENDER_DIR)/basic_draws.c
RENDER_OBJS = $(RENDER_CFILES:.c=.o)

# hooks
HOOKS_DIR = ./src/hooks
HOOKS_HEADER = $(HOOKS_DIR)/local_hooks.h
HOOKS_CFILES = 	$(HOOKS_DIR)/set_hooks.c \
				$(HOOKS_DIR)/actions_I.c \
				$(HOOKS_DIR)/actions_II.c \
				$(HOOKS_DIR)/updates.c \
				$(HOOKS_DIR)/controls.c
HOOKS_OBJS = $(HOOKS_CFILES:.c=.o)

#parse
PARSE_DIR = ./src/parse
PARSE_HEADER = $(PARSE_DIR)/local_parse.h
PARSE_CFILES = \
				$(PARSE_DIR)/parse_file.c \
				$(PARSE_DIR)/parse_line.c \
				$(PARSE_DIR)/check_line.c \
				$(PARSE_DIR)/build_map.c \
				$(PARSE_DIR)/find_player.c \
				$(PARSE_DIR)/set_color.c \
				$(PARSE_DIR)/set_texture.c \
				$(PARSE_DIR)/free_utils.c \
				$(PARSE_DIR)/validate_data.c \
				$(PARSE_DIR)/free_validating.c
PARSE_OBJS = $(PARSE_CFILES:.c=.o)

# Libft
LIBFT_DIR = $(LIBRARYS)/Libft
LIBFT_HEADER_DIR = $(LIBFT_DIR)/include
LIBFT = $(LIBFT_DIR)/libft.a

all : $(NAME)

$(NAME) : $(MAIN_OBJS) $(PARSE_OBJS) $(LIBFT) $(UTILS_OBJS) $(HOOKS_OBJS) $(HOOKS_HEADER) $(UTILS_HEADER) $(RAYCAST_OBJS) $(RENDER_OBJS) $(RENDER_HEADER)
	cc $(FLAGS) $(MAIN_OBJS) $(PARSE_OBJS) $(UTILS_OBJS) $(RAYCAST_OBJS) $(RENDER_OBJS) $(HOOKS_OBJS) $(LDFLAGS) $(MLX_L) -o $(NAME)

$(MAIN_DIR)/%.o: $(MAIN_DIR)/%.c $(INCLUDE_PATH)/$(TYPES) $(MAIN_HEADER)
	cc $(FLAGS) -I $(INCLUDE_PATH) -I $(LIBFT_HEADER_DIR) -I $(INCLUDE_MLX) -c $< -o $@

$(UTILS_DIR)/%.o: $(UTILS_DIR)/%.c $(INCLUDE_PATH)/$(TYPES) $(UTILS_HEADER)
	cc $(FLAGS) -I $(INCLUDE_PATH) -I $(UTILS_DIR) -I $(INCLUDE_MLX) -I $(LIBFT_HEADER_DIR) -c $< -o $@

$(HOOKS_DIR)/%.o: $(HOOKS_DIR)/%.c $(INCLUDE_PATH)/$(TYPES) $(HOOKS_HEADER)
	cc $(FLAGS) -I $(INCLUDE_PATH) -I $(HOOKS_DIR) -I $(INCLUDE_MLX) -I $(LIBFT_HEADER_DIR) -c $< -o $@

$(RAYCAST_DIR)/%.o: $(RAYCAST_DIR)/%.c $(INCLUDE_PATH)/$(TYPES) $(RAYCAST_HEADER) 
	cc $(FLAGS) -I $(INCLUDE_PATH) -I $(RAYCAST_DIR) -I $(LIBFT_HEADER_DIR) -c $< -o $@

$(RENDER_DIR)/%.o: $(RENDER_DIR)/%.c $(INCLUDE_PATH)/$(TYPES) $(RENDER_HEADER) 
	cc $(FLAGS) -I $(INCLUDE_PATH) -I $(INCLUDE_MLX) -I $(RENDER_DIR) -I $(LIBFT_HEADER_DIR) -c $< -o $@

$(PARSE_DIR)/%.o: $(PARSE_DIR)/%.c $(INCLUDE_PATH)/$(TYPES) $(PARSE_HEADER) 
	$(CC) $(CFLAGS) -I $(PARSE_DIR) -I $(INCLUDE_PATH) -I $(LIBFT_HEADER_DIR) -c $< -o $@

$(LIBFT) :
	$(MAKE) -C $(LIBFT_DIR)

clean :
	rm -rf $(MAIN_OBJS)
	rm -rf $(PARSE_OBJS)
	rm -rf $(UTILS_OBJS)
	rm -rf $(HOOKS_OBJS)
	rm -rf $(RAYCAST_OBJS)
	rm -rf $(RENDER_OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean : clean
	rm -rf $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re : fclean all

.PHONY : all clean fclean re