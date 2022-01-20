/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 12:20:42 by tyuan             #+#    #+#             */
/*   Updated: 2020/05/10 21:16:23 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	docp(char **tab, char const *s, int *ct)
{
	int	i;

	tab[ct[2]] = ft_malloc(sizeof(char) * (ct[1] - ct[0]));
	i = 0;
	while (ct[0] + 1 + i < ct[1])
	{
		tab[ct[2]][i] = s[ct[0] + 1 + i];
		i++;
	}
	tab[ct[2]][i] = '\0';
	ct[2]++;
	return (1);
}

static int	sizet(char const *s, char c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (*s)
	{
		if (*s == c)
			i++;
		s++;
	}
	return (i);
}

static void	init(int count[3])
{
	count[0] = -1;
	count[1] = 0;
	count[2] = 0;
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		count[3];

	init(count);
	if (s == NULL)
		return (NULL);
	tab = ft_malloc(sizeof(char *) * (sizet(s, c) + 2));
	while (s[count[1]])
	{
		if (s[count[1]] == c || s[count[1] + 1] == '\0')
		{
			if (s[count[1] + 1] == '\0' && s[count[1]] != c)
				count[1]++;
			if (count[1] - count[0] != 1)
			{
				if (!(docp(tab, s, count)))
					return (NULL);
			}
			count[0] = count[1];
		}
		if (s[count[1]])
			count[1]++;
	}
	tab[count[2]] = NULL;
	return (tab);
}
