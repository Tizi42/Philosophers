/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 21:01:57 by tyuan             #+#    #+#             */
/*   Updated: 2020/08/18 14:09:42 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	print_c(char chr, t_printf *format)
{
	if (format->flag_minus)
	{
		write(1, &chr, 1);
		putchr_multi(' ', format->width - 1);
	}
	else
	{
		putchr_multi(' ', format->width - 1);
		write(1, &chr, 1);
	}
	return (ternary(format->width > 1, format->width, 1));
}

int	print_s(char *str, t_printf *format)
{
	int		maxstr;
	char	*s;
	char	c;

	s = str;
	maxstr = printf_strlen(str);
	if (maxstr == -1)
	{
		maxstr = 6;
		s = "(null)";
	}
	if (format->precision >= 0 && format->precision < maxstr)
		maxstr = format->precision;
	if (format->flag_minus)
	{
		write(1, s, maxstr);
		putchr_multi(' ', format->width - maxstr);
	}
	else
	{
		c = checkflagzero(format);
		putchr_multi(c, format->width - maxstr);
		write(1, s, maxstr);
	}
	return (ternary(format->width > maxstr, format->width, maxstr));
}

int	print_p(void *ptr, t_printf *format)
{
	char	*hexa;
	char	len;

	hexa = ft_malloc(sizeof(char) * 12);
	if (ptradrr(ptr, hexa, format) == 1)
		len = 1;
	else
		len = checkptr(hexa);
	len = pointer(len, hexa, format);
	free(hexa);
	return (len);
}

int	print_percentage(t_printf *format)
{
	char	c;

	c = ' ';
	if (format->flag_minus)
	{
		write(1, "%", 1);
		putchr_multi(c, format->width - 1);
	}
	else
	{
		if (format->flag_zero)
			c = '0';
		putchr_multi(c, format->width - 1);
		write(1, "%", 1);
	}
	return (ternary(format->width > 1, format->width, 1));
}
