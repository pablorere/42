
NAME = Unnecessary_violence
CPP = c++
CPPFLAGS = -Wall -Werror -Wextra -std=c++98 -g3
SRCS = main.cpp Weapon.cpp HumanA.cpp HumanB.cpp 
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(CPPFLAGS) $(OBJS) -o $(NAME)
%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re 