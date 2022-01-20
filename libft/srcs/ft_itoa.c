/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 18:30:31 by tyuan             #+#    #+#             */
/*   Updated: 2020/05/12 15:36:08 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	itoa_ir(long int nb, char *res, size_t *id)
{
	if (nb < 10)
		res[(*id)++] = nb + 48;
	else if (nb >= 10)
	{
		itoa_ir(nb / 10, res, id);
		res[(*id)++] = nb % 10 + 48;
	}
	return (*id);
}

static int	itoa_size(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	char		*res;
	long int	nb;
	size_t		i;

	res = ft_malloc(sizeof(char) * (itoa_size(n) + 1));
	nb = n;
	i = 0;
	if (nb < 0)
	{
		res[i++] = '-';
		nb = -nb;
	}
	i = (size_t)itoa_ir(nb, res, &i);
	res[i] = '\0';
	return (res);
}
