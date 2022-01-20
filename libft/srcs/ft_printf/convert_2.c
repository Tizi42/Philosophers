/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 19:10:12 by tyuan             #+#    #+#             */
/*   Updated: 2020/08/18 13:11:15 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	print_di(int n, t_printf *format)
{
	int			nega;
	int			clen;
	int			nlen;
	long int	nb;

	if (checkzero(n, format))
		return (ternary(format->width > 0, format->width, 0));
	nb = n;
	nega = ternary(nb < 0, 1, 0);
	nb = ternary(nega == 1, -nb, nb);
	nlen = len(nb);
	clen = nlen;
	if (format->precision > clen && format->precision >= 0)
		clen = format->precision;
	di(nega, (clen += nega), nb, format);
	return (ternary(format->width > clen, format->width, clen));
}

void	di(int nega, int lenth, long int n, t_printf *format)
{
	int		nlen;
	char	c;

	c = ' ';
	nlen = len(n);
	if (format->flag_minus)
	{
		checknega(nega);
		putchr_multi('0', format->precision - nlen);
		f_putnbr(n);
		putchr_multi(c, format->width - lenth);
	}
	else
	{
		if (format->flag_zero && format->precision < 0)
		{
			c = '0';
			checknega(nega);
		}
		putchr_multi(c, format->width - lenth);
		if (nega && c == ' ')
			write(1, "-", 1);
		putchr_multi('0', format->precision - nlen);
		f_putnbr(n);
	}
}

int	print_u(unsigned int n, t_printf *format)
{
	int		lenth;
	int		nlen;

	if (checkzero(n, format))
		return (ternary(format->width > 0, format->width, 0));
	nlen = len(n);
	lenth = nlen;
	if (format->precision >= 0 && format->precision > nlen)
		lenth = format->precision;
	di(0, lenth, n, format);
	return (ternary(format->width > lenth, format->width, lenth));
}

int	print_x(unsigned int n, t_printf *format, char s)
{
	int		lenth;
	int		nlen;
	char	*hexa;

	if (checkzero(n, format))
		return (ternary(format->width > 0, format->width, 0));
	nlen = len_x(n);
	lenth = nlen;
	hexa = tohexa(n, nlen, s);
	if (format->precision >= 0 && format->precision > nlen)
		lenth = format->precision;
	xx(hexa, nlen, lenth, format);
	free(hexa);
	return (ternary(format->width > lenth, format->width, lenth));
}

void	xx(char *hexa, int nlen, int lenth, t_printf *format)
{
	char	c;

	if (format->flag_minus)
	{
		putchr_multi('0', format->precision - nlen);
		write(1, hexa, nlen);
		putchr_multi(' ', format->width - lenth);
	}
	else
	{
		c = checkflagzero(format);
		putchr_multi(c, format->width - lenth);
		putchr_multi('0', format->precision - nlen);
		write(1, hexa, nlen);
	}
}
