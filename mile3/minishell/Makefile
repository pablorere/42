# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/01 00:00:00 by ppaula-s          #+#    #+#              #
#    Updated: 2025/11/10 14:04:40 by ppaula-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
INCLUDES	= -I./include -I./include/libft

LIBFT_DIR	= ./include
LIBFT		= $(LIBFT_DIR)/libft.a

OBJ_DIR		= obj
SRCS_DIR	= srcs

SRCS		= main.c srcs/signals.c \
			  srcs/utils.c \
			  srcs/builtins.c
OBJS		= $(addprefix $(OBJ_DIR)/, $(notdir $(SRCS:.c=.o)))

LIBS		= -lreadline
ifneq ($(wildcard $(LIBFT)),)
	LIBS += -L$(LIBFT_DIR) -lft
endif

all: $(NAME)

$(LIBFT):
	@if [ -f $(LIBFT_DIR)/Makefile ]; then \
		make -C $(LIBFT_DIR); \
	else \
		echo "Warning: libft Makefile not found. Skipping libft compilation."; \
	fi

$(NAME): $(LIBFT) $(OBJS)
	@if [ -f $(LIBFT) ]; then \
		$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME); \
	else \
		$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME); \
	fi

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@if [ -f $(LIBFT_DIR)/Makefile ]; then \
		make clean -C $(LIBFT_DIR) 2>/dev/null || true; \
	fi
	rm -rf $(OBJ_DIR)

fclean: clean
	@if [ -f $(LIBFT_DIR)/Makefile ]; then \
		make fclean -C $(LIBFT_DIR) 2>/dev/null || true; \
	fi
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
