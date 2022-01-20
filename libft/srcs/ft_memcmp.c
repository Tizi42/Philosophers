/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 10:40:01 by tyuan             #+#    #+#             */
/*   Updated: 2020/05/06 11:56:08 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	while (n > 0)
	{
		if (*(char *)s1 != *(char *)(s2))
			return (*((unsigned char *)s1) - *(unsigned char *)s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}
