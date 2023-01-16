/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:20:24 by ebillon           #+#    #+#             */
/*   Updated: 2022/11/08 17:20:26 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
Calloc allocated count objects that are size bytes of memory, \
these are filled with 0 value.
Return a pointer of the allocated memory, or null.
*/

void	*ft_calloc(size_t count, size_t size)
{
	void	*pointer;

	if (count > 0 && size > ULONG_MAX / count)
		return (NULL);
	pointer = malloc(size * count);
	if (!pointer)
		return (NULL);
	ft_bzero(pointer, size * count);
	return (pointer);
}
