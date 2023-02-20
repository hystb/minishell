/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 12:45:23 by ebillon           #+#    #+#             */
/*   Updated: 2023/02/06 14:48:28 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Free and applies (*del) on lst element.	
*/

void	ft_lstdelone(t_list *lst, void (*del)(void **))
{
	if (!lst || !del)
		return ;
	(*del)(lst->content);
	free(lst);
}
