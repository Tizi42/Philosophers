/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   within_int_limit.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 16:46:05 by tyuan             #+#    #+#             */
/*   Updated: 2022/01/21 16:46:46 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_atoui(const char *str)
{
	unsigned int	n;

	n = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		n *= 10;
		n += (*str - 48);
		str++;
	}
	return (n);
}

int	within_int_limit(char *tab, int size)
{
	unsigned int	n;
	int				signe;

	signe = 0;
	if (tab[0] == '-')
		signe = 1;
	if (size > 10 + signe || (size == 10 + signe && tab[signe] > '2'))
		return (0);
	n = ft_atoui(tab);
	if ((n > 2147483647 && signe == 0) || n > 2147483648)
		return (0);
	return (1);
}
