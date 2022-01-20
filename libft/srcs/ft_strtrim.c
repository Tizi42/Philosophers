/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 11:52:28 by tyuan             #+#    #+#             */
/*   Updated: 2020/05/06 17:54:48 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	test(char s1, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (s1 == set[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	int		i;
	int		j;
	int		len;

	if (s1 == NULL)
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	while (s1[i] && test(s1[i], set) == 0)
		i++;
	len -= 1;
	while (len >= i && test(s1[len], set) == 0)
		len--;
	trim = ft_malloc(sizeof(char) * (len - i + 2));
	j = 0;
	while (len >= i + j)
	{
		trim[j] = s1[i + j];
		j++;
	}
	trim[j] = '\0';
	return (trim);
}
