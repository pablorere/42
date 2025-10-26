NAME = philo

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -f

SRC = meu\ filo/main.c \
      meu\ filo/utils.c \
      meu\ filo/parsing.c \
      meu\ filo/init.c \
      meu\ filo/routine.c \
      meu\ filo/simulation.c \
      meu\ filo/monitor.c \
      meu\ filo/cleanup.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re