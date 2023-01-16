/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:07:46 by ebillon           #+#    #+#             */
/*   Updated: 2022/11/15 12:07:47 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Add the element NEW at the beggining of lst.	
*/

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new)
		return ;
	if (lst)
		new->next = *lst;
	*lst = new;
}
