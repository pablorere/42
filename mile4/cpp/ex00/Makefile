NAME        = megaphone
CXX         = c++
CXXFLAGS    = -Wall -Wextra -Werror -std=c++98
SRCS        = megaphone.cpp ToUpper.cpp
OBJS        = $(SRCS:.cpp=.o)

GREEN       = \033[0;32m
RED         = \033[0;31m
YELLOW      = \033[0;33m
RESET       = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "$(GREEN)Megaphone compiled successfully!$(RESET)"

%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@for obj in $(OBJS); do \
		if [ -f $$obj ]; then \
			rm -f $$obj; \
			echo "$(RED)Eliminado: $$obj$(RESET)"; \
		else \
			echo "$(YELLOW)Falta (no existe): $$obj$(RESET)"; \
		fi; \
	done

fclean: clean
	@if [ -f $(NAME) ]; then \
		rm -f $(NAME); \
		echo "$(RED)Eliminado ejecutable: $(NAME)$(RESET)"; \
	else \
		echo "$(YELLOW)Falta (no existe): $(NAME)$(RESET)"; \
	fi

re: fclean all

.PHONY: all clean fclean re

