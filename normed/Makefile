# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/23 16:53:05 by tkatolik          #+#    #+#              #
#    Updated: 2019/06/11 01:07:46 by tkatolik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= fdf

OBJDIR	:=	obj
LIBXDIR	:=	./minilibx
LFTDIR	:=	./libft

SRC		:=	fdf.c \
			fdf_2.c \
			get_source_data.c \
			get_source_data_2.c \
			draw.c \
			draw_2.c \
			hooks.c \
			hooks_2.c \
			hooks_3.c \
			info.c \
			info_2.c \
			utility.c \
			projections.c \
			projections_2.c \

OBJ		:=	$(addprefix $(OBJDIR)/,$(SRC:.c=.o))

CC		:=	gcc
#DEBUG	:=	-g
#DEBUG	+=	-fsanitize=address

FLAGS	:=	-Wall -Wextra -Werror
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
