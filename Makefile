

NAME = Cub3D

CC = gcc 

SRC_DIR = sources

SRC =  sources/main.c \
	sources/ft_parsing.c \
	sources/ft_read_map.c \
	sources/ft_window.c \
	sources/ft_orientation.c \
	sources/ft_deplacements.c \
	sources/ft_textures.c \
	sources/ft_bmp.c \
	sources/ft_sprite.c \
	sources/ft_utils.c \
	sources/ft_check_error.c \
	sources/ft_utils_2.c \
	sources/ft_sprite_2.c \

OBJ = $(SRC:%.c=%.o)

IFLAGS = -I./includes -I./libft

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=undefined

LIBS =  -L./libft  -lft  -lmlx   -framework OpenGL  -framework AppKit

all: $(NAME)

%.o: %.c
	gcc $(CFLAGS) $(IFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@make -s  -C libft
	gcc $(CFLAGS) $(IFLAGS) $(SRC) $(LIBS) -o $(NAME)

clean:
	make clean -C libft
	rm -f $(SRC_DIR)/*.o

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

show:
	@echo "CFLAGS :\n  $(CFLAGS)"
	@echo "IFLAGS :\n  $(IFLAGS)"

re: fclean all



.PHONY: all clean fclean re
