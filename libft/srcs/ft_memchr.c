/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 10:10:20 by tyuan             #+#    #+#             */
/*   Updated: 2020/05/06 10:29:05 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned const char	*rep;
	size_t				i;

	rep = s;
	i = 0;
	while (i < n)
	{
		if (rep[i] == (unsigned char)c)
			return ((void *)&rep[i]);
		i++;
	}
	return (NULL);
}
