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

#parse
PARSE_DIR = ./src/parse
PARSE_HEADER = $(PARSE_DIR)/local_parse.h
PARSE_CFILES = \
				$(PARSE_DIR)/parse_input.c \
				$(PARSE_DIR)/parse_line.c \
				$(PARSE_DIR)/check_line.c \
				$(PARSE_DIR)/build_map.c \
				$(PARSE_DIR)/find_player.c \
				$(PARSE_DIR)/set_color.c \
				$(PARSE_DIR)/set_texture.c \
				$(PARSE_DIR)/free_utils.c \
				$(PARSE_DIR)/validate_input.c \
				$(PARSE_DIR)/free_validating.c
PARSE_OBJS = $(PARSE_CFILES:.c=.o)


OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(PARSE_OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(PARSE_OBJS) $(LIBFT) -o $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I $(INCLUDE_PATH) -I $(LIBFT_HEADER_DIR) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(PARSE_DIR)/%.o: $(PARSE_DIR)/%.c $(PARSE_HEADER)
	$(CC) $(CFLAGS) -I $(PARSE_DIR) -I $(INCLUDE_PATH) -I $(LIBFT_HEADER_DIR) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -f $(PARSE_OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
