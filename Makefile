NAME = cub3D
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

INCLUDE_PATH = ./headers
SRC_DIR = ./src

LIBS_DIR = ./libs
LIBFT_DIR = $(LIBS_DIR)/Libft
LIBFT_HEADER_DIR = $(LIBFT_DIR)/include
LIBFT = $(LIBFT_DIR)/libft.a

SRC = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/parse/parse_input.c \
	$(SRC_DIR)/parse/parse_line.c \
	$(SRC_DIR)/parse/check_line.c \
	$(SRC_DIR)/parse/build_map.c \
	$(SRC_DIR)/parse/find_player.c \
	$(SRC_DIR)/parse/set_color.c \
	$(SRC_DIR)/parse/set_texture.c \
	$(SRC_DIR)/parse/free_utils.c \
	$(SRC_DIR)/validating/validate_input.c \
	$(SRC_DIR)/validating/free_validating.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I $(INCLUDE_PATH) -I $(LIBFT_HEADER_DIR) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
