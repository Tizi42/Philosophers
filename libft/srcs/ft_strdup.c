/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 11:08:24 by tyuan             #+#    #+#             */
/*   Updated: 2020/05/12 16:14:16 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		size;
	char	*cp;

	cp = ft_malloc(sizeof(char) * (ft_strlen(s1) + 1));
	size = 0;
	while (s1[size])
	{
		cp[size] = s1[size];
		size++;
	}
	cp[size] = '\0';
	return (cp);
}
