NAME = cub3D

LIBFT = lib/libft.a

CC = cc

CFLAGS =	-Wall -Wextra -Werror -g \
			-Iinclude

LFLAGS =	-Llib \
			-lmlx42 -lft -ldl -lglfw -pthread -lm

SRC_DIR = src/
OBJ_DIR = obj/
FILES =	main \
		parsing/init_map # parsing/utils_parsing

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

all: $(NAME)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -rf $(NAME)
	make fclean -C lib

re: fclean all

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -o $@ $(OBJS) $(LFLAGS)

$(LIBFT):
	make -C lib

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re bonus