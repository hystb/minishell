/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:07:31 by ebillon           #+#    #+#             */
/*   Updated: 2022/11/07 14:07:58 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
Function which 
- return 1, if c is an ascii caracter
- return 0, if c isn't an ascii caracter
*/

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	return (0);
}
