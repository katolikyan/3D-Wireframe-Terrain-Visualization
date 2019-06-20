# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/23 16:53:05 by tkatolik          #+#    #+#              #
#    Updated: 2019/06/08 23:15:10 by tkatolik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= fdf

OBJDIR	:=	obj
LIBXDIR	:=	./minilibx
LFTDIR	:=	./libft

SRC		:=	fdf.c \
			get_source_data.c \
			draw.c \
			hooks.c \
			info.c \
			utility.c \
			projections.c \

OBJ		:=	$(addprefix $(OBJDIR)/,$(SRC:.c=.o))

CC		:=	gcc
#DEBUG	:=	-g
#DEBUG	+=	-fsanitize=address

FLAGS	:=	-Wall -Wextra -Werror -O3
FLAGS	+=	-c -I.
MLIBX	:=	-L minilibx -lmlx -framework OpenGL -framework AppKit

all: $(NAME)
	@echo "\n\n______________ ALL: EVERYTHING IS DONE ______________\n\n"

$(NAME): OBJ
	$(CC) $(OBJ) -o $(NAME) -L $(LFTDIR) -lft $(MLIBX)
	@echo "\n __________ (NAME): DONE ________\n\n"

OBJ: LIB
	mkdir $(OBJDIR)
	$(CC) -g $(FLAGS) $(SRC)
	mv *.o ./$(OBJDIR)
	@echo "\n __________ (OBJ): DONE ________\n\n"

LIB:	
	@make -C $(LFTDIR)
	@make -C $(LIBXDIR)
	@echo "\n __________ LIB: DONE ________\n\n"

clean:
	@make -C $(LFTDIR) clean
	@make -C $(LIBXDIR) clean
	rm -rf $(OBJDIR)
	@echo "\n __________ CLEAN: DONE ________\n\n"

fclean: clean
	@make -C $(LFTDIR) fclean
	@make -C $(LIBXDIR) fclean
	rm -f $(NAME)
	@echo "\n __________ FCLEAN: DONE ________\n\n"

re: fclean all
