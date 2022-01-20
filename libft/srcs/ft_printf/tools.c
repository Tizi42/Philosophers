/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/09 17:39:02 by tyuan             #+#    #+#             */
/*   Updated: 2020/08/18 13:39:28 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	putchr_multi(char c, int times)
{
	while (times-- > 0)
		write(1, &c, 1);
}

int	printf_strlen(char *str)
{
	int	l;

	l = 0;
	if (!(str))
		return (-1);
	while (str[l])
		l++;
	return (l);
}

int	expo_2(unsigned int n)
{
	unsigned int	i;
	unsigned int	j;

	i = 1;
	j = 0;
	while (j++ < n)
		i *= 2;
	return (i);
}

char	deci_hexa(int n)
{
	char	*hexa;

	hexa = "0123456789abcdef";
	if (n < 0 || n > 15)
		return (-1);
	else
		return (hexa[n]);
}

int	ptradrr(void *ptr, char *hexa, t_printf *format)
{
	int	x[2];
	int	i;
	int	nb;

	if (!ptr && format->precision < 0)
	{
		hexa[0] = '0';
		return (1);
	}
	x[1] = 0;
	i = 0;
	while (x[1] < 12)
	{
		x[0] = 0;
		nb = 0;
		while (x[0] < 4)
		{
			i = ((long int)ptr >> (x[1] * 4 + x[0])) & 1;
			nb += expo_2(x[0]) * i;
			x[0]++;
		}
		hexa[11 - x[1]] = deci_hexa(nb);
		x[1]++;
	}
	return (0);
}
