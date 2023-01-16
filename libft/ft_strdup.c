/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:09:19 by ebillon           #+#    #+#             */
/*   Updated: 2022/11/11 11:09:20 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
Fonction which copy *s1 into a new *char ALLOCATED by the function. 
Return pointer of this new *char.
*/

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*res;

	len = ft_strlen(s1);
	res = ft_calloc(len + 1, sizeof(char));
	if (res)
		ft_strlcpy(res, s1, len + 1);
	return (res);
}
