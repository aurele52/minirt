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

FILE=	ft_printdroite2.c	\
		main.c	\
		ft_printdroite3.c	\
		ft_printdroite.c	\
		ft_printsp.c	\
		ft_cast.c	\
		libft/ft_strjoin.c	\
		libft/ft_putnbrfd.c	\
		libft/ft_substr.c \
		libft/ft_setpos.c	\
		libft/ft_lstnew.c	\
		libft/ft_lstdelone.c	\
		libft/ft_malloc.c		\
		libft/ft_strlen.c	\
		libft/ft_strcmp.c	\
		libft/ft_posclear.c \
		libft/ft_strdup.c	\
		libft/ft_split.c \
		libft/ft_itoa.c	\
		libft/ft_max.c	\
		libft/ft_min.c	\
		libft/ft_atoi.c	\
		libft/get_next_line.c	\
		libft/get_next_line_utils.c	\
		libft/ft_exit.c	\
		libft/ft_abs.c

SRC_DIR = src/

SRC = $(addprefix $(SRC_DIR),$(FILE))

OBJ			=	$(SRC:.c=.o)

DOBJ		=	${SRC:.c=.d}

NAME = rt

INC = include/rt.h

CC = clang

FLAGS = -Wall -Werror -Wextra -MMD
FLAGS = -g -Wall -Werror -Wextra -MMD

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
