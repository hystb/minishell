/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:38:08 by ebillon           #+#    #+#             */
/*   Updated: 2022/11/08 16:38:10 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
Function which locate the last occurence of c and return a pointer on it.
*/
char	*ft_strrchr(const char *s, int c)
{
	char	*occ;

	occ = NULL;
	while (*s)
	{
		if (*s++ == (char) c)
			occ = ((char *)(s - 1));
	}
	if (*s == c)
		return ((char *)(s));
	return (occ);
}
