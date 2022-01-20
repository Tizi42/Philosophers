# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/05 21:07:48 by tyuan             #+#    #+#              #
#    Updated: 2020/11/10 18:12:37 by tyuan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

CFILES	= ft_atoi.c       ft_memccpy.c    ft_putstr_fd.c  ft_strncmp.c ft_bzero.c      ft_memchr.c     ft_split.c      ft_strnstr.c   ft_calloc.c     ft_memcmp.c     ft_strchr.c     ft_strrchr.c   ft_isalnum.c    ft_memcpy.c     ft_strdup.c     ft_strtrim.c ft_isalpha.c    ft_memmove.c    ft_strjoin.c    ft_substr.c    ft_isascii.c    ft_memset.c     ft_strlcat.c    ft_tolower.c   ft_isdigit.c    ft_putchar_fd.c ft_strlcpy.c    ft_toupper.c  ft_isprint.c    ft_putendl_fd.c ft_strlen.c   ft_itoa.c       ft_putnbr_fd.c  \
				ft_strmapi.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
				get_next_line_utils.c get_next_line.c \
				ft_printf/convert_2.c ft_printf/ft_printf.c ft_printf/tools_2.c ft_printf/convert_1.c ft_printf/ft_format.c ft_printf/tools.c     ft_printf/tools_3.c
CFILES	+= ternary.c ft_min.c ft_swap.c ft_malloc.c free_split.c sizeof_tab.c

SRCS	= ${addprefix srcs/, ${CFILES}}

OBJS	= ${SRCS:.c=.o}

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror -I includes/

HEAD	= libft.h

RM	= rm -f

all:	${NAME}

${NAME}:	${OBJS}
	ar rc $@ $^
	chmod +x ${NAME}

clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re:		fclean all

.PHONY:	all clean fclean re
