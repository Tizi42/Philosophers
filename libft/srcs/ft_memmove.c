/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 17:03:53 by tyuan             #+#    #+#             */
/*   Updated: 2020/05/12 15:19:27 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t		i;
	char		*dstcp;

	if (dst == NULL && src == NULL)
		return (dst);
	i = len;
	dstcp = dst;
	if (src < dst)
	{
		while (len--)
			*(char *)(dst + len) = *(char *)(src + len);
	}
	else
	{
		while (i--)
			*(char *)(dstcp++) = *(char *)(src++);
	}
	return (dst);
}
