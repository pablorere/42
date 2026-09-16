NAME        = FragTrap02

# Compiler and mandatory 42 flags
CC          = c++
CFLAGS      = -Wall -Wextra -Werror -std=c++98

# Directories
SRCS_DIR    = srcs
OBJS_DIR    = objs

# Source files (.cpp) in srcs/
SRCS        = Main.cpp \
              $(SRCS_DIR)/ClapTrap.cpp\
			   $(SRCS_DIR)/ScavTrap.cpp\
			   $(SRCS_DIR)/FragTrap.cpp

# Map source files to their .o objects in objs/
OBJS        = $(SRCS:$(SRCS_DIR)/%.cpp=$(OBJS_DIR)/%.o)

# Header search paths (root and srcs/)
INCLUDES    = -I. -I$(SRCS_DIR)

# Terminal colors
GREEN       = \033[1;32m
RED         = \033[1;31m
YELLOW      = \033[1;33m
BLUE        = \033[1;34m
RESET       = \033[0m

# Main rule
all: $(NAME)

# Build the executable (avoids unnecessary relink)
$(NAME): $(OBJS)
	@echo "$(BLUE)Linking objects and building $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJS) $(INCLUDES) -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(RESET)"

# Compile each srcs/*.cpp into objs/*.o
$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	@mkdir -p $(OBJS_DIR)
	@echo "$(YELLOW)Compiling: $<...$(RESET)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Remove object files (objs/)
clean:
	@if [ -d "$(OBJS_DIR)" ]; then \
		echo "$(RED)Removing object directory $(OBJS_DIR)/...$(RESET)"; \
		rm -rf $(OBJS_DIR); \
	fi

# Full clean (objects + executable)
fclean: clean
	@if [ -f "$(NAME)" ]; then \
		echo "$(RED)Removing executable $(NAME)...$(RESET)"; \
		rm -f $(NAME); \
	fi

# Rebuild from scratch
re: fclean all

# Avoid conflicts with files that share target names
.PHONY: all clean fclean re