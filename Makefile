# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: audreyer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/21 22:50:22 by audreyer          #+#    #+#              #
#    Updated: 2022/12/15 13:18:56 by audreyer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILE=	all.c \
		cast.c	\
		print.c	\
		tree.c	\
		utils.c	\
		parse.c


SRC_DIR = src/

SRC = $(addprefix $(SRC_DIR),$(FILE))

OBJ			=	$(SRC:.c=.o)

DOBJ		=	${SRC:.c=.d}

NAME = rt

INC = include/rt.h

CC = clang

FLAGS = -g -MMD

RM			=	rm -f

all:		$(NAME)

-include ${DOBJ}
.c.o:
			$(CC) $(FLAGS) -I include -c $< -o $(<:.c=.o)

$(NAME):	$(OBJ) $(INC)
	$(CC) $(FLAGS) $(OBJ) -L./minilibx-linux -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
			${RM} $(OBJ) ${DOBJ}

fclean:		clean
			${RM} $(NAME)

re:			fclean all 

INC_LIBFT = include/libft.h

LIB = $(SRC_DIR)libft.a

.PHONY:		all clean fclean re .c.o
