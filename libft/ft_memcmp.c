/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:48:01 by ebillon           #+#    #+#             */
/*   Updated: 2022/11/08 16:48:05 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
Return the resulst of the comparison between *s1 and *s2, these strings \
are assumed to be n bytes long.
*/

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const char	*a;
	const char	*b;
	int			temp;

	a = s1;
	b = s2;
	temp = 0;
	while (temp == 0 && n--)
	{
		if (*a != *b)
			temp = (unsigned const char) *a - (unsigned const char) *b;
		a++;
		b++;
	}
	return (temp);
}
