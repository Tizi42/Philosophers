/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 11:31:04 by tyuan             #+#    #+#             */
/*   Updated: 2020/05/10 17:13:03 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*a;
	size_t	t1;
	size_t	t2;

	t1 = 0;
	t2 = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	a = ft_malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	while (s1[t1])
	{
		a[t1] = s1[t1];
		t1++;
	}
	while (s2[t2])
	{
		a[t1 + t2] = s2[t2];
		t2++;
	}
	a[t1 + t2] = '\0';
	return (a);
}
