/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 16:10:28 by ebillon           #+#    #+#             */
/*   Updated: 2022/11/07 16:10:29 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
Fonction which copy n bytes from *src to *dst. 
Return value : inital pointer of dst. May overlaps.
*/

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*dst_;
	const char	*src_;

	if (dst != NULL && src != NULL)
	{
		dst_ = dst;
		src_ = src;
		while (n--)
		{
			*dst_ = *src_;
			src_++;
			dst_++;
		}
	}
	return (dst);
}
