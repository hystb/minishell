/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:09:29 by ebillon           #+#    #+#             */
/*   Updated: 2022/11/11 11:09:31 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
Fonction which extract a part of *s starting a start caracters + s, /
and ending at maximum len caracters.
Return the extracted part, in form of a ALLOCATED string. 
*/

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	int		size;

	if (!s)
		return (NULL);
	size = 0;
	if (start < ft_strlen(s))
		s = s + start;
	else
		s = s + ft_strlen(s);
	while (*s++ && len--)
		size++;
	s = s - size - 1;
	res = ft_calloc(size + 1, sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, s, size + 1);
	return (res);
}
