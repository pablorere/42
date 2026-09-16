# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppaula-s <ppaula-s@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/09/14 16:19:12 by ppaula-s          #+#    #+#              #
#    Updated: 2025/09/14 16:20:31 by ppaula-s         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Este Makefile compila el proyecto push_swap y el bonus checker.
# Cada sección y target está comentada en español para facilitar la comprensión.

NAME = push_swap      # Nombre del ejecutable principal
CC = gcc              # Compilador utilizado
RM = rm -f            # Comando para eliminar archivos
FLAGS = -Wall -Wextra -Werror   # Flags de compilación para mostrar advertencias
LIBFTDIR = libft/     # Carpeta de la librería libft
OBJ_DIR = obj/        # Carpeta para archivos objeto (no usada en este Makefile)
BONUS = checker       # Nombre del ejecutable bonus
SRC_DIR = srcs/       # Carpeta de los archivos fuente

# Archivo principal de push_swap
SRC_1 = srcs/push_swap/push_swap.c \

# Archivos fuente adicionales para push_swap
SRC_2 =\
		srcs/push_swap/ft_atoi2.c \
		srcs/push_swap/ft_add_back.c \
		srcs/push_swap/ft_stack_new.c \
		srcs/push_swap/ft_check_utils.c \
		srcs/push_swap/ft_parse.c \
		srcs/push_swap/solver_utils_ab.c \
		srcs/push_swap/solver_utils_ba.c \
		srcs/push_swap/ft_rotate_and_push.c \
		srcs/push_swap/operations.c \
		srcs/push_swap/operations_2.c \
		srcs/push_swap/operations_3.c \
		srcs/push_swap/ft_check_dup.c \
		srcs/push_swap/ft_check_sorted.c \
		srcs/push_swap/ft_error_print.c \
		srcs/push_swap/ft_free.c \
		srcs/push_swap/lst_utils.c \
		srcs/push_swap/lst_utils_2.c \
		srcs/push_swap/ft_parse_args_quoted.c \
		srcs/push_swap/ft_list_args.c \
		srcs/push_swap/ft_check_args.c \
		srcs/push_swap/ft_sort_big.c \
		srcs/push_swap/ft_sort_three.c \
		srcs/push_swap/ft_rotate_type.c \

# Archivos fuente para el bonus checker
BONUS_SRC = srcs/checker/checker.c \
			srcs/checker/checker_utils.c \

# Objetos generados a partir de los fuentes
OBJ_1 = ${SRC_1:.c=.o}      # Objetos del archivo principal
OBJ_2 = ${SRC_2:.c=.o}      # Objetos de los archivos adicionales
BONUS_OBJ =${BONUS_SRC:.c=.o}   # Objetos del bonus

# Parámetro para enlazar la librería libft
INCLUDE = -L ./libft -lft

# Regla para compilar archivos .c a .o
# Se ejecuta automáticamente cuando se necesita un .o
.c.o:
	${CC} -c $< -o ${<:.c=.o}

# Target principal: compila el ejecutable push_swap
${NAME}: ${OBJ_1} ${OBJ_2}
	make -C $(LIBFTDIR)        # Compila la librería libft
	${CC} ${FLAGS} ${OBJ_1} ${OBJ_2} -o ${NAME} ${INCLUDE}   # Enlaza todo y genera el ejecutable

# Target bonus: compila el ejecutable checker
${BONUS}: ${OBJ_2} ${BONUS_OBJ} 
	make -C $(LIBFTDIR)        # Compila la librería libft
	${CC} ${FLAGS} ${BONUS_OBJ} ${OBJ_2} -o ${BONUS} ${INCLUDE}   # Enlaza todo y genera el bonus

# Target all: compila ambos ejecutables (push_swap y checker)
all: ${NAME} ${BONUS}

# Target bonus: compila solo el bonus checker
bonus: ${BONUS} 

# Target clean: elimina los archivos objeto y ejecutables generados
clean:
	${RM} ${OBJ_1} ${OBJ_2} ${BONUS_OBJ} ${NAME} ${BONUS}
	@cd $(LIBFTDIR) && $(MAKE) clean   # Limpia también los objetos de libft

# Target fclean: elimina todos los archivos generados, incluyendo libft
fclean: clean
	${RM} ${NAME}
	@cd $(LIBFTDIR) && $(MAKE) fclean  # Limpia también los ejecutables de libft

# Target re: limpia y recompila todo desde cero
re: clean all

# Indica que estos targets no son archivos
.PHONY: all clean fclean re bonus