/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 09:31:07 by tyuan             #+#    #+#             */
/*   Updated: 2020/05/04 11:12:00 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static int	ft_strlen(const char *str)
{
	int	l;

	l = 0;
	while (str[l])
		l++;
	return (l);
}

size_t	ft_strlcat(char *restrict dst, const char *restrict src,
		size_t dstsize)
{
	int	i;
	int	lendst;

	lendst = 0;
	while (*dst)
	{
		lendst++;
		dst++;
	}
	i = 0;
	while (src[i] && i < (int)dstsize - lendst - 1)
	{
		*dst = src[i];
		dst++;
		i++;
	}
	*dst = '\0';
	if ((int)dstsize > lendst)
		return (ft_strlen(src) + lendst);
	else
		return (ft_strlen(src) + dstsize);
}
