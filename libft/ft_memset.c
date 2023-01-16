/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:10:19 by ebillon           #+#    #+#             */
/*   Updated: 2022/11/07 14:10:27 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
Function to set len value of b to c. Return value : initial pointer
*/

void	*ft_memset(void *b, int c, size_t len)
{
	char	*start;
	int		i;

	i = -1;
	start = b;
	while (len--)
		start[++i] = c;
	return (b);
}
