PROG	= pipex
PROG_B	= pipex_bonus

SRCS	= pipex.c ft_utils.c
OBJS	= $(SRCS:.c=.o)

SRCS_B	= pipex_bonus.c utils.c utils_bonus.c
OBJS_B	= $(SRCS_B:.c=.o)

HEADER	= -Iincludes -Ilibft

CC		= gcc
CFLAGS	= -Wall -Wextra -Werror -g

%.o: %.c
	$(CC) $(CFLAGS) $(HEADER) -c $< -o $@

all: $(PROG)

$(PROG): $(OBJS)
	make -C libft
	$(CC) $(OBJS) -Llibft -lft -o $(PROG)

bonus: $(PROG_B)

$(PROG_B): $(OBJS_B)
	make -C libft
	$(CC) $(OBJS_B) -Llibft -lft -o $(PROG_B)

clean:
	make clean -C libft
	rm -f $(OBJS) $(OBJS_B)

fclean: clean
	make fclean -C libft
	rm -f $(PROG) $(PROG_B)

re: fclean all

re_bonus: fclean bonus

.PHONY: all clean fclean re re_bonus bonus