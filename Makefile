# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/16 19:10:22 by tyuan             #+#    #+#              #
#    Updated: 2022/01/27 09:44:30 by tyuan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

SRCS	= main.c parse.c init.c simulation.c monitor.c shared.c

DIRSRC	= srcs

OBJS	= ${addprefix ${DIROBJ}/, ${SRCS:.c=.o}}

DIROBJ	= objs

LIBS	= -Llibft -lft

CC		= gcc

CFLAGS	= -Wall -Wextra -Werror

INCLUDE	= -I include/ -I libft/includes/

HEADER	= philo.h

RM	= rm -rf

all:	${NAME}

${NAME}: ${OBJS}
	make -C libft
	${CC} ${CFLAGS} ${INCLUDE} $^ ${LIBS} -o $@

${DIROBJ}:
	mkdir -p $@

${DIROBJ}/%.o: ${DIRSRC}/%.c | ${DIROBJ}
	${CC} ${CFLAGS} ${INCLUDE} -c $< -o $@

clean:
	make clean -s -C libft
	${RM} ${DIROBJ}

fclean: clean
	make fclean -s -C libft
	${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re
