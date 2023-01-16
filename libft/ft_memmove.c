/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 17:12:28 by ebillon           #+#    #+#             */
/*   Updated: 2022/11/07 17:12:50 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
Fonction which copy len bytes from *src to *dst.
Return value : inital pointer of dst. Copy in reverse if src > dst to /
avoid overlaps.
*/

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;

	if (dst == NULL && src == NULL)
		return (dst);
	if (dst > src)
	{
		s = src + len - 1;
		d = dst + len - 1;
		while (len--)
			*d-- = *s--;
	}
	else
	{
		s = src;
		d = dst;
		while (len--)
			*d++ = *s++;
	}
	return (dst);
}
