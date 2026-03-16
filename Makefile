NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = src
SRC_INIT_DIR = src/init
INCLUDE_DIR = includes
LIBFT_DIR = libft
MLX_DIR = minilibx-linux

SRC = 	$(SRC_DIR)/main.c \
	$(SRC_INIT_DIR)/init_mlx.c

OBJ = $(SRC:.c=.o)

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lm -lX11 -lXext

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) \
		-o $(NAME) $(OBJ) -L$(LIBFT_DIR) -lft $(MLX_FLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@

clean:
	rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

