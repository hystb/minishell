/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:09:42 by ebillon           #+#    #+#             */
/*   Updated: 2022/11/11 11:09:43 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Fonction which concatenate s1 and s2 in a string ALLOCATED.
Return the new string.
*/

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	int		len;

	if ((!s1 || !s2) || (!s1 && !s2))
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	res = ft_calloc(len + 1, sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcat(res, s1, ft_strlen(s1) + 1);
	ft_strlcat(res, s2, len + 1);
	return (res);
}
