NAME = philo
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -I$(INC_DIR)
RM = rm -f

SRC = main.c \
      init.c \
      routine.c \
      monitor.c \
      utils.c

SRCS = $(addprefix $(SRC_DIR)/, $(SRC))
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/philo.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re