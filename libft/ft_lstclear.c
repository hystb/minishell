/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:50:55 by ebillon           #+#    #+#             */
/*   Updated: 2022/11/15 12:50:56 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Applies ft_lstdelone to all the element after *lst.	
*/

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*i;
	t_list	*temp;

	if (!lst)
		return ;
	i = *lst;
	while (i)
	{
		temp = i->next;
		ft_lstdelone(i, (*del));
		i = temp;
	}
	*lst = NULL;
}
