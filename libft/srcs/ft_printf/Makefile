# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tyuan <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/14 13:08:56 by tyuan             #+#    #+#              #
#    Updated: 2020/08/18 13:03:29 by tyuan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libftprintf.a

SRCS	= ft_printf.c	ft_format.c	convert_1.c	convert_2.c	tools.c	tools_2.c tools_3.c

OBJS	= ${SRCS:.c=.o}

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

HEAD	= printf.h

RM	= rm -f

all:	${NAME}

${NAME}:	${OBJS}
	ar rc ${NAME} $^

bonus: all

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re:		fclean all

.PHONY: all bonus clean fclean re
