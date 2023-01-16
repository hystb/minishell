/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:31:42 by ebillon           #+#    #+#             */
/*   Updated: 2022/11/15 13:31:55 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Do the same as ft_lstiter but put the result on a new allocated list. 	
*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*nlist;

	if ((!lst || !(*f)))
		return (0);
	nlist = ft_lstnew(f(lst->content));
	if (!nlist)
		return (NULL);
	lst = lst->next;
	while (lst)
	{
		ft_lstadd_back(&nlist, ft_lstnew(f(lst->content)));
		if (!lst)
		{
			ft_lstclear(&lst, del);
			return (NULL);
		}
		lst = lst->next;
	}
	return (nlist);
}
