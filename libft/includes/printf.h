/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 20:09:30 by tyuan             #+#    #+#             */
/*   Updated: 2020/11/10 16:21:20 by ValarMorg        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define RESET   "\033[0m"
# define BLACK   "\033[30m"
# define RED     "\033[31m"
# define GREEN   "\033[32m"
# define YELLOW  "\033[33m"
# define BLUE    "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN    "\033[36m"
# define WHITE   "\033[37m"
# define BOLDBLACK   "\033[1m\033[30m"
# define BOLDRED     "\033[1m\033[31m"
# define BOLDGREEN   "\033[1m\033[32m"
# define BOLDYELLOW  "\033[1m\033[33m"
# define BOLDBLUE    "\033[1m\033[34m"
# define BOLDMAGENTA "\033[1m\033[35m"
# define BOLDCYAN    "\033[1m\033[36m"
# define BOLDWHITE   "\033[1m\033[37m"

typedef struct s_printf
{
	int	width;
	int	precision;
	int	flag_zero;
	int	flag_minus;
}				t_printf;

int				ft_printf(const char *str, ...);
t_printf		*printf_lstnew(void);
int				print_arg(char *str, int i, va_list ap, int *p);
int				checkzero(long int n, t_printf *format);
int				checkptr(char *hexa);

void			putchr_multi(char c, int times);
int				printf_strlen(char *str);
int				expo_2(unsigned int n);
char			deci_hexa(int n);
int				ptradrr(void *ptr, char *hexa, t_printf *format);

int				len(long int n);
void			f_putnbr(long int nb);
int				len_x(long int n);
char			*tohexa(long int n, int nlen, char s);
void			stock_x(long int n, int nlen, char *hexa, char *base);

int				flags(char s, t_printf *format);
int				width(char s, t_printf *format, va_list ap);
int				precision(char s, t_printf *format, va_list ap);
int				type(char s, t_printf *format, va_list ap);

int				print_c(char chr, t_printf *format);
int				print_s(char *str, t_printf *format);
int				print_p(void *ptr, t_printf *format);
int				print_percentage(t_printf *format);

int				print_di(int n, t_printf *format);
void			di(int nega, int nlen, long int n, t_printf *format);
int				print_u(unsigned int n, t_printf *format);
int				print_x(unsigned int n, t_printf *format, char s);
void			xx(char *hexa, int nlen, int lenth, t_printf *format);

void			checknega(int nega);
char			checkflagzero(t_printf *format);
int				pointer(int len, char *hexa, t_printf *format);

#endif
