/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:39:37 by ebillon           #+#    #+#             */
/*   Updated: 2022/11/08 15:39:39 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
Fonction which copy *src ot *dst and adding the NULL-Terminating caracter.
Return value : inital lenght of *src.
*/

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	res;

	res = (ft_strlen(src));
	if (dstsize <= 0)
		return (res);
	while (--dstsize && *src)
		*dst++ = *src++;
	*dst = '\0';
	return (res);
}
