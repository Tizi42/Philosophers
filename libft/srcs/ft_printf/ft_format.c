/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 15:49:21 by tyuan             #+#    #+#             */
/*   Updated: 2020/08/18 12:35:27 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	flags(char s, t_printf *format)
{
	if (s == '-')
		format->flag_minus = 1;
	else if (s == '0')
		format->flag_zero = 1;
	else
		return (0);
	return (1);
}

int	width(char s, t_printf *format, va_list ap)
{
	int	n;

	n = 0;
	if (s == '*')
	{
		n = va_arg(ap, int);
		if (n < 0)
		{
			n = -n;
			format->flag_minus = 1;
		}
	}
	else
	{
		if (format->width > 0)
			n = format->width;
		n *= 10;
		n += s - '0';
	}
	format->width = n;
	return (1);
}

int	precision(char s, t_printf *format, va_list ap)
{
	unsigned int	n;

	n = 0;
	if (s == '*')
		n = va_arg(ap, unsigned int);
	else
	{
		if (format->precision > 0)
			n = format->precision;
		n *= 10;
		n += s - '0';
	}
	format->precision = n;
	return (1);
}

int	type(char s, t_printf *format, va_list ap)
{
	int	p;

	if (s == 'd' || s == 'i')
		p = print_di(va_arg(ap, int), format);
	else if (s == 'u')
		p = print_u(va_arg(ap, unsigned int), format);
	else if (s == 'x' || s == 'X')
		p = print_x(va_arg(ap, int), format, s);
	else if (s == 'c')
		p = print_c(va_arg(ap, int), format);
	else if (s == 's')
		p = print_s(va_arg(ap, char *), format);
	else if (s == 'p')
		p = print_p(va_arg(ap, void *), format);
	else if (s == '%')
		p = print_percentage(format);
	else
		p = -1;
	return (p);
}
