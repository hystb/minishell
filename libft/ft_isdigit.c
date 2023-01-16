/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:00:31 by ebillon           #+#    #+#             */
/*   Updated: 2022/11/07 14:05:41 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
Function which 
- return 1, if c is a digit caracter
- return 0, if c isn't an digit caracter
*/

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}
