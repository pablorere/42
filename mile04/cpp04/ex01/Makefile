NAME        = animal

CC          = c++
CFLAGS      = -Wall -Wextra -Werror -std=c++98

OBJS_DIR    = objs

SRCS        = main.cpp \
              Animal.cpp \
              Dog.cpp \
              Cat.cpp \
              Brain.cpp \
              WrongAnimal.cpp \
              WrongCat.cpp

OBJS        = $(SRCS:%.cpp=$(OBJS_DIR)/%.o)

INCLUDES    = -I.

GREEN       = \033[1;32m
RED         = \033[1;31m
YELLOW      = \033[1;33m
BLUE        = \033[1;34m
RESET       = \033[0m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(BLUE)Linking objects and building $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

$(OBJS_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling: $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@if [ -d "$(OBJS_DIR)" ]; then \
		echo "$(RED)Removing object directory $(OBJS_DIR)/...$(RESET)"; \
		rm -rf $(OBJS_DIR); \
	fi

fclean: clean
	@if [ -f "$(NAME)" ]; then \
		echo "$(RED)Removing executable $(NAME)...$(RESET)"; \
		rm -f $(NAME); \
	fi

re: fclean all

.PHONY: all clean fclean re
