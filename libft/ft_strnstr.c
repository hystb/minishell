/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:49:56 by ebillon           #+#    #+#             */
/*   Updated: 2023/03/27 13:58:23 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Function which locate the first occurence of *needle in *haystack /
but search at max len caracters and return a pointer on it.
NULL is retured if needle not found
*haystack is returned if needle is empty
*/

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		j;

	i = 0;
	if (!*needle)
		return (NULL);
	if ((!haystack || !needle) && !len)
		return (0);
	while (haystack[i] && i < len)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < len && haystack[i])
		{
			if (!needle[j + 1] && !haystack[j + 1])
				return ((char *)(haystack + i));
			j++;
		}
		i++;
	}
	return (NULL);
}
