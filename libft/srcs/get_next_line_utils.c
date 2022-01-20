/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/31 19:00:40 by tyuan             #+#    #+#             */
/*   Updated: 2020/06/04 14:25:48 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "printf.h"
#include "get_next_line.h"

char	*f_strdup(const char *s1)
{
	int		size;
	char	*cp;

	cp = ft_malloc(sizeof(char) * (f_strlen(s1) + 1));
	size = 0;
	while (s1 && s1[size])
	{
		cp[size] = s1[size];
		size++;
	}
	cp[size] = '\0';
	return (cp);
}

t_fdnl	*checkfd(t_fdnl *begin, int fd)
{
	while (begin)
	{
		if (fd == begin->ifd)
			return (begin);
		begin = begin->next;
	}
	return (NULL);
}

t_fdnl	*f_lstnew(int fd)
{
	t_fdnl	*new;

	new = ft_malloc(sizeof(*new));
	new->ifd = fd;
	new->iline = NULL;
	new->next = NULL;
	return (new);
}

void	f_lstadd_back(t_fdnl **alst, t_fdnl *new)
{
	if (*alst == NULL)
	{
		*alst = new;
		return ;
	}
	while (alst && (*alst)->next)
		alst = &((*alst)->next);
	(*alst)->next = new;
}

void	del_istruct(t_fdnl **begin, t_fdnl **istruct)
{
	t_fdnl	*cur;
	t_fdnl	*next;

	if ((*begin)->ifd == (*istruct)->ifd)
	{
		*begin = (*istruct)->next;
		free(*istruct);
		return ;
	}
	next = *begin;
	while (next)
	{
		cur = next;
		next = cur->next;
		if (next->ifd == (*istruct)->ifd)
		{
			cur->next = (*istruct)->next;
			free(*istruct);
			return ;
		}
	}
}
