NAME = fixed_test

SRC = main.cpp Fixed.cpp
OBJ = $(SRC:.cpp=.o)


CC = g++ -Wall -Wextra -g3 -O3 -Werror -std=c++98

all: $(NAME)

$(NAME):
	$(CC) -o $(NAME) $(SRC)

clean:
	rm -rf $(OBJ)
fclean:
	rm -rf $(OBJ) $(NAME)
re:
	make clean	
	make all

.PHONY: all clean fclean re