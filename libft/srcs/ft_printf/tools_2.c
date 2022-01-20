/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 10:54:07 by tyuan             #+#    #+#             */
/*   Updated: 2020/08/18 12:49:59 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	len(long int n)
{
	int	len;

	len = 1;
	n = n / 10;
	while (n != 0)
	{
		len++;
		n = n / 10;
	}
	return (len);
}

void	f_putnbr(long int nb)
{
	if (nb < 0)
	{
		nb = -nb;
		write(1, "-", 1);
	}
	if (nb < 10)
		putchr_multi(nb + '0', 1);
	else if (nb >= 10)
	{
		f_putnbr(nb / 10);
		putchr_multi(nb % 10 + '0', 1);
	}
}

int	len_x(long int n)
{
	int	len;

	len = 1;
	n = n / 16;
	while (n > 0)
	{
		len++;
		n = n / 16;
	}
	return (len);
}

char	*tohexa(long int n, int nlen, char s)
{
	char	*base;
	char	*hexa;

	base = "0123456789abcdef";
	if (s == 'X')
		base = "0123456789ABCDEF";
	hexa = ft_malloc(sizeof(char) * nlen);
	stock_x(n, nlen, hexa, base);
	return (hexa);
}

void	stock_x(long int n, int nlen, char *hexa, char *base)
{
	if (n / 16 != 0)
		stock_x(n / 16, nlen - 1, hexa, base);
	hexa[nlen - 1] = base[n % 16];
}
