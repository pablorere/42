NAME = Towards_a_more_useful_fixed_point_number_class

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
	make fclean	
	make all

.PHONY: all clean fclean re