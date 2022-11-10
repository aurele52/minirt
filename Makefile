# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: audreyer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/21 22:50:22 by audreyer          #+#    #+#              #
#    Updated: 2022/11/08 18:47:01 by audreyer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rt

CC = gcc

FLAG = -g -Wall -Werror -Wextra 

SRC=	src/ft_printdroite2.c	\
		src/ft_printdroite3.c	\
		src/ft_printdroite.c	\
		src/ft_printsp.c	\
		src/main.c	\
		src/ft_cast.c	\
		src/libft/ft_strjoin.c	\
		src/libft/ft_putnbrfd.c	\
		src/libft/ft_substr.c \
		src/libft/ft_setpos.c	\
		src/libft/ft_lstnew.c	\
		src/libft/ft_lstdelone.c	\
		src/libft/ft_malloc.c		\
		src/libft/ft_strlen.c	\
		src/libft/ft_strcmp.c	\
		src/libft/ft_posclear.c \
		src/libft/ft_strdup.c	\
		src/libft/ft_split.c \
		src/libft/ft_itoa.c	\
		src/libft/ft_max.c	\
		src/libft/ft_min.c	\
		src/libft/ft_atoi.c	\
		src/libft/get_next_line.c	\
		src/libft/get_next_line_utils.c	\
		src/libft/ft_exit.c	\
		src/libft/ft_abs.c

OBJ = $(SRC:.c=.o)

.c.o:
	$(CC) $(FLAG) -I include -c $< -o $(<:.c=.o)

INC = include/rt.h

all:	$(NAME)

$(NAME):	$(OBJ) $(INC)
	$(CC) $(FLAG) $(OBJ) -L./minilibx-linux -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
	rm -f $(OBJ) libft.a

fclean:	clean
	rm -f $(NAME)

re			: fclean all 

.PHONY: all clean fclean re libft
