/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:04:16 by nmilan            #+#    #+#             */
/*   Updated: 2022/11/15 12:04:16 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list	*tmp;

	tmp = (*lst);
	if (lst)
	{
		if (*lst)
		{
			new->next = *lst;
			tmp->previous = new;
			*lst = new;
		}
		else
		{
			*lst = new;
		}
	}
}
