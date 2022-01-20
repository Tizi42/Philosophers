/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 20:06:49 by tyuan             #+#    #+#             */
/*   Updated: 2020/08/18 12:55:37 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

t_printf	*printf_lstnew(void)
{
	t_printf	*new;

	new = ft_malloc(sizeof(*new));
	new->width = -1;
	new->precision = -1;
	new->flag_zero = 0;
	new->flag_minus = 0;
	return (new);
}

int	print_arg(char *str, int i, va_list ap, int *p)
{
	t_printf	*format;
	int			j;

	format = printf_lstnew();
	while (flags(str[i], format))
		i++;
	while ((str[i] >= '0' && str[i] <= '9') || str[i] == '*')
		i += width(str[i], format, ap);
	if (str[i] == '.')
	{
		i++;
		format->precision = 0;
		while ((str[i] >= '0' && str[i] <= '9') || str[i] == '*')
			i += precision(str[i], format, ap);
	}
	j = type(str[i], format, ap);
	if (j == -1)
		i--;
	else
		*p += j;
	free(format);
	return (i);
}

int	checkzero(long int n, t_printf *format)
{
	if (n == 0 && format->precision == 0)
	{
		putchr_multi(' ', format->width);
		return (1);
	}
	return (0);
}

int	checkptr(char *hexa)
{
	int	i;
	int	j;
	int	len;

	i = 1;
	j = 0;
	len = 12;
	if (hexa[0] == '0')
	{
		while (hexa[i] == '0')
			i++;
		len = 12 - i;
		while (i < 12)
		{
			hexa[j] = hexa[i];
			i++;
			j++;
		}
	}
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		p;

	i = 0;
	p = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			i = print_arg((char *)str, i, ap, &p);
		}
		else
		{
			write(1, &str[i], 1);
			p++;
		}
		i++;
	}
	va_end(ap);
	return (p);
}
