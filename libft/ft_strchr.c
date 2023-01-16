/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:34:50 by ebillon           #+#    #+#             */
/*   Updated: 2022/11/08 16:34:51 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
Function which locate the first occurence of c and return a pointer on it.
*/

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s++ == (char) c)
			return ((char *)(--s));
	}
	if (*s == c)
		return ((char *)(s));
	return (NULL);
}
