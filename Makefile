# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/15 23:54:02 by angavrel          #+#    #+#              #
#    Updated: 2017/02/18 16:00:10 by angavrel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

SRC_PATH = srcs
OBJ_PATH = obj
INC_PATH = incl
LIBFT_PATH = libft

SRC = main.c \
	  fractol.c \
	  algorytms.c \
	  algorytms2.c \
	  hook.c \
	  key_hook.c \
	  color.c \

LIBFT = -L $(LIBFT_PATH) -lft -lm

MINILIBX = -lmlx -framework OpenGl -framework AppKit

FLAGS = -Wall -Werror -Wextra

OBJ = $(addprefix $(OBJ_PATH)/,$(SRC:.c=.o))

INC = -I $(INC_PATH) -I $(LIBFT_PATH)

all: lib $(NAME)

lib:
	@make -C $(LIBFT_PATH)

$(NAME) : $(OBJ)
	@clang $(FLAGS) -o $(NAME) $(LIBFT) $(MINILIBX) $^
	@echo "\n\033[36;1m"$@ "program created\033[0m"
	@printf '\033[32;1m~~~~~~~~~~~~~~~~~~~~~~~~\n\033[0m'

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@clang $(FLAGS) $(INC) -o $@ -c $<
	@printf '\033[32;1m~~~~~~\033[0m'

clean:
	@echo "\033[31m.o files supressed\033[0m"
	@rm -rf $(OBJ_PATH)
	@make -C libft/ clean

fclean: clean
	@echo "\033[31mProgram deleted\033[0m"
	@rm -rf $(NAME)
	@make -C libft/ fclean

re: fclean all

norme:
	@norminette src/$(SRC)
	@norminette $(INC_PATH)/*.h

.PHONY: all lib clean fclean re norme
