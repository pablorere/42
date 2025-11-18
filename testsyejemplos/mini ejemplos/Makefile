# Mini Philosophers Makefile

NAME = mini_philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -g
RM = rm -f

SRC = mini_philo.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c mini_philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: all
	./$(NAME) 5

.PHONY: all clean fclean re run
