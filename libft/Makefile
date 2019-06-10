#a **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/02/13 17:12:52 by tkatolik          #+#    #+#              #
#    Updated: 2019/05/16 09:49:54 by tkatolik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

OBJ_DIR = obj
SRC_DIR = src
INC_DIR = inc

SRCS	=	$(SRC_DIR)/*.c
OBJ		=	$(OBJ_DIR)/*.o
CC		=	gcc
FLAGS	=	-Wall -Wextra -Werror -c -I $(INC_DIR)/*.h

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)	

$(OBJ):
	$(CC) $(FLAGS) $(SRCS)
	mkdir $(OBJ_DIR) 
	mv *.o ./$(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all
