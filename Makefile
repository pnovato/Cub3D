NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = src
SRC_INIT_DIR = src/init
SRC_PARSING_DIR = src/parsing
SRC_RENDER_DIR = src/render
INCLUDE_DIR = includes
OBJ_DIR = objs
LIBFT_DIR = libft
MLX_DIR = minilibx-linux

SRC = $(SRC_DIR)/main.c \
      $(SRC_INIT_DIR)/init_mlx.c \
      $(SRC_INIT_DIR)/init_player.c \
      $(SRC_PARSING_DIR)/parser.c \
      $(SRC_PARSING_DIR)/parse_elements.c\
      $(SRC_PARSING_DIR)/validate_map.c \
      $(SRC_RENDER_DIR)/render.c \
      $(SRC_RENDER_DIR)/draw.c

OBJ = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC))

MLX_FLAGS = -L$(MLX_DIR) -lmlx -lm -lX11 -lXext

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) \
		-o $(NAME) $(OBJ) -L$(LIBFT_DIR) -lft $(MLX_FLAGS)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -I$(INCLUDE_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -c $< -o $@

clean:
	rm -f $(OBJ)
	@make -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re

