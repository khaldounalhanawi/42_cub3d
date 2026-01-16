NAME = cub3D
FLAGS = -Wall -Wextra -Werror
INCLUDE_PATH = ./headers
TYPES = data_types.h

# for main
MAIN_DIR = ./src
MAIN_CFILES = $(MAIN_DIR)/main.c $(MAIN_DIR)/tester.c
MAIN_OBJS = $(MAIN_CFILES:.c=.o)


all : $(NAME)

$(NAME) : $(MAIN_OBJS) 
	cc $(FLAGS) $(MAIN_OBJS) -o $(NAME)

$(MAIN_DIR)/%.o: $(MAIN_DIR)/%.c $(INCLUDE_PATH)/$(TYPES) $(INCLUDE_PATH)/main.h
	cc $(FLAGS) -I $(INCLUDE_PATH) -c $< -o $@

clean :
	rm -rf $(MAIN_OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re