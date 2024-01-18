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
		parsing/init_map parsing/utils_parsing parsing/verificator parsing/valid_map \
		raycasting/raycasting raycasting/init_raycasting raycasting/utils_buffer raycasting/directions raycasting/rotate utils

SRCS = $(addprefix $(SRC_DIR), $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(FILES)))

all: $(NAME)

bonus: all

clean :
	@rm -rf $(OBJ_DIR)

fclean : clean
	@rm -rf $(NAME)
	@make fclean -C lib

re: fclean all

$(NAME): $(OBJS) $(LIBFT)
	@echo "\033[32m✔ Compilating sources files...\033[37m"
	@$(CC) -o $@ $(OBJS) $(LFLAGS)
	@echo "\033[32m✔ Executable created.\033[37m"

$(LIBFT):
	@make -C lib

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all clean fclean re bonus