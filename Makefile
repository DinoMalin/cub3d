NAME = cub3D

LIBFT = lib/libft.a

CC = cc

CFLAGS =	-Wall -Wextra -Werror -g \
			-Iinclude

LFLAGS =	-Llib \
			-lmlx42 -lft -ldl -lglfw -pthread

SRC_DIR = src/
OBJ_DIR = obj/
FILES = main
SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

all: $(NAME)

clean :
	rm -rf $(OBJ_DIR)
	make fclean -C lib

fclean : clean
	rm -rf $(NAME)
	make fclean -C lib

re: fclean all

$(NAME): $(OBJ_DIR) $(OBJS) $(LIBFT)
	$(CC) -o $@ $(OBJS) $(LFLAGS)

$(LIBFT):
	make -C lib

$(OBJ_DIR):
	mkdir $@

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re bonus