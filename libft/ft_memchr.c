/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:45:15 by ebillon           #+#    #+#             */
/*   Updated: 2022/11/08 16:45:17 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
Function which locate the first occurence of c in *s and return a pointer on it.
*/

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*schar;
	void		*res;

	schar = s;
	while (n--)
	{
		if ((unsigned char)*schar++ == (unsigned char)c)
		{
			res = (void *)(schar - 1);
			return (res);
		}
	}
	return (NULL);
}
