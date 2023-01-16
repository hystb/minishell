/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:14:27 by ebillon           #+#    #+#             */
/*   Updated: 2022/11/15 10:14:29 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Applies the funciton (*f) on all the caracters o *s, unsigned int \
correspod to i.
*/

void	*ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	int	i;

	i = -1;
	if (!s)
		return (0);
	while (s[++i])
	{
		if (f)
			(*f)(i, &s[i]);
	}
	return (s);
}
