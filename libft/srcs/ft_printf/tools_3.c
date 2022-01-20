/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 12:53:47 by tyuan             #+#    #+#             */
/*   Updated: 2020/08/18 14:10:44 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	checknega(int nega)
{
	if (nega)
		write(1, "-", 1);
}

char	checkflagzero(t_printf *format)
{
	if (format->flag_zero && format->precision < 0)
		return ('0');
	return (' ');
}

int	pointer(int len, char *hexa, t_printf *format)
{
	int	lenth;

	lenth = len;
	if (format->precision > 0 && !(len == 1 && hexa[0] == '0'))
		lenth = ternary(format->precision > len, format->precision, len);
	if (format->flag_minus)
	{
		write(1, "0x", 2);
		write(1, hexa, len);
		putchr_multi(' ', format->width - 2 - len);
	}
	else
	{
		putchr_multi(' ', format->width - 2 - lenth);
		write(1, "0x", 2);
		putchr_multi('0', lenth - len);
		write(1, hexa, len);
	}
	return (ternary(format->width > lenth + 2, format->width, lenth + 2));
}
