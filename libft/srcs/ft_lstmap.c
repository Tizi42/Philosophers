/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tyuan <tyuan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 12:48:51 by tyuan             #+#    #+#             */
/*   Updated: 2020/05/12 16:11:16 by tyuan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newl;
	t_list	*elem;

	if (lst == NULL || f == NULL)
		return (NULL);
	if (lst)
	{
		newl = ft_lstnew((*f)(lst->content));
		if (!newl)
		{
			(*del)(lst->content);
			return (NULL);
		}
		lst = lst->next;
	}
	while (lst)
	{
		elem = ft_lstnew((*f)(lst));
		lst = lst->next;
		ft_lstadd_back(&newl, elem);
	}
	return (newl);
}
