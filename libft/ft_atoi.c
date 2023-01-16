/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:55:25 by ebillon           #+#    #+#             */
/*   Updated: 2022/11/08 16:55:26 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

/*
Function which convert the ascii number to an intenger number.
*/

int	ft_atoi(const char *str)
{
	long	res;
	int		sign;
	int		i;

	i = 0;
	res = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || (str[i] == 32))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	while (ft_isdigit(str[i]) == 1)
	{
		if (res != ((res * 10 + (sign * (str[i] - '0'))) / 10))
		{
			if (sign < 0)
				return (0);
			return (-1);
		}
		res = res * 10 + sign * (str[i++] - '0');
	}
	return (res);
}
