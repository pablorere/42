CC = cc

CFLAGS = -Wall -Werror -Wextra

NAME = libftprintf.a

SRCS = ft_printf.c ft_utils.c 
all: $(NAME)

AR = ar

ARFLAGS = rcs

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re