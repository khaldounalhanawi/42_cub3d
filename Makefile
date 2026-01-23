NAME = cub3D
FLAGS = -Wall -Wextra -Werror
INCLUDE_PATH = ./headers
SRC_DIR = ./src

LIBS_DIR = ./libs
LIBFT_DIR = $(LIBS_DIR)/Libft
LIBFT_HEADER_DIR = $(LIBFT_DIR)/include
LIBFT = $(LIBFT_DIR)/libft.a

SRC = \
$(SRC_DIR)/main.c \
$(SRC_DIR)/tester.c \
$(SRC_DIR)/parse_input.c \
$(SRC_DIR)/parse_line.c \
$(SRC_DIR)/check_line.c \
$(SRC_DIR)/finalize_parse.c \
$(SRC_DIR)/find_player.c

OBJS = $(SRC:.c=.o)

all : $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	cc $(FLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(INCLUDE_PATH)/data_types.h $(INCLUDE_PATH)/main.h
	cc $(FLAGS) -I $(INCLUDE_PATH) -I $(LIBFT_HEADER_DIR) -c $< -o $@

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
