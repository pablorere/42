NAME = so_long
CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
SRC = src/main.c src/utils.c src/map_loader.c src/draw.c src/hooks.c src/init.c src/validation.c src/move.c
OBJS = $(SRC:.c=.o)
MLXFLAGS = -L lib/mlx -lmlx -lX11 -lXext -lm
LIBFT = lib/libftfull/libft/libft.a
MLX = lib/mlx/libmlx.a

all: $(NAME)

$(NAME): $(OBJS) $(MLX) $(LIBFT)
	$(CC) $(OBJS) $(MLXFLAGS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Ilib/mlx -Ilib/libftfull/libft -c $< -o $@

$(MLX):
	$(MAKE) -C lib/mlx

$(LIBFT):
	$(MAKE) -C lib/libftfull/libft

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C lib/mlx
	$(MAKE) clean -C lib/libftfull/libft

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C lib/libftfull/libft

re: fclean all

.PHONY: all clean fclean re
