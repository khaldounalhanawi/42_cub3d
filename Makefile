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
MAIN_CFILES = $(MAIN_DIR)/main.c $(MAIN_DIR)/tester.c
MAIN_OBJS = $(MAIN_CFILES:.c=.o)

# utils
UTILS_DIR = ./src/utils
UTILS_CFILES = $(UTILS_DIR)/init_system.c
UTILS_OBJS = $(UTILS_CFILES:.c=.o)

# Libft
LIBFT_DIR = $(LIBRARYS)/Libft
LIBFT_HEADER_DIR = $(LIBFT_DIR)/include
LIBFT = $(LIBFT_DIR)/libft.a

all : $(NAME)

$(NAME) : $(MAIN_OBJS) $(LIBFT) $(UTILS_OBJS)
	cc $(FLAGS) $(MAIN_OBJS) $(UTILS_OBJS) $(LDFLAGS) $(MLX_L) -o $(NAME)

$(MAIN_DIR)/%.o: $(MAIN_DIR)/%.c $(INCLUDE_PATH)/$(TYPES) $(INCLUDE_PATH)/main.h
	cc $(FLAGS) -I $(INCLUDE_PATH) -I $(LIBFT_HEADER_DIR) -I $(INCLUDE_MLX) -c $< -o $@

$(UTILS_DIR)/%.o: $(UTILS_DIR)/%.c $(INCLUDE_PATH)/$(TYPES)
	cc $(FLAGS) -I $(INCLUDE_PATH) -I $(INCLUDE_MLX) -I $(LIBFT_HEADER_DIR) -c $< -o $@

$(LIBFT) :
	$(MAKE) -C $(LIBFT_DIR)

clean :
	rm -rf $(MAIN_OBJS)
	rm -rf $(UTILS_OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean : clean
	rm -rf $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re : fclean all

.PHONY : all clean fclean re