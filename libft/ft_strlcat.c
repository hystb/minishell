/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 15:49:55 by ebillon           #+#    #+#             */
/*   Updated: 2022/11/08 15:49:56 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
Concatenate src at the end of src.
*/

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	int		i;

	if ((!dst || !src) && !dstsize)
		return (0);
	len_dst = ft_strlen(dst);
	i = 0;
	if (dstsize < 0)
		return (ft_strlen(src));
	if (dstsize < len_dst)
		return (ft_strlen(src) + dstsize);
	while (dstsize > len_dst + i + 1 && src[i])
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = '\0';
	return (len_dst + ft_strlen(src));
}
