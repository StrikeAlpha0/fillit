# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jthompki <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/17 00:53:09 by jthompki          #+#    #+#              #
#    Updated: 2017/12/21 13:51:13 by msharpe          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

INC = -I libft/

LNK = -L libft/ -lft

FLAG = -Wall -Werror -Wextra

HEADER = fillit.h

OBJ = list.o\
	  main.o\
	  read_input.o\
	  solve.o\

all: $(NAME)

$(NAME):
	@make -C ./libft
	@gcc $(FLAG) -c $(OBJ:.o=.c) $(INC)
	@gcc $(FLAG) $(INC) $(LNK) -o $(NAME) $(OBJ) 

clean:
	@/bin/rm -f $(OBJ) fillit.h.gch
	@make -C ./libft fclean

fclean: clean
	@/bin/rm -f $(NAME)

re: fclean all
