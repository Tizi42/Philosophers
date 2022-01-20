/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 12:49:19 by tyuan             #+#    #+#             */
/*   Updated: 2020/05/06 15:38:49 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((*s1 || *s2) && i < n)
	{
		if ((unsigned char)*s1 > (unsigned char)*s2)
			return (1);
		else if ((unsigned char)*s1 < (unsigned)*s2)
			return (-1);
		s1++;
		s2++;
		i++;
	}
	return (0);
}
