/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_hutils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 12:12:29 by ebillon           #+#    #+#             */
/*   Updated: 2023/01/16 13:34:13 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printf_puthex_aux(unsigned long nbr, int *count, int start)
{
	if (nbr >= 16)
		if (printf_puthex_aux(nbr / 16, count, start) == -1)
			return (-1);
	if (nbr % 16 >= 10)
	{
		if (printf_putchar(start + nbr % 16 % 10) == -1)
			return (-1);
		*count += 1;
	}
	else
	{
		if (printf_putchar('0' + nbr % 16) == -1)
			return (-1);
		*count += 1;
	}
	return (0);
}

int	printf_puthex(unsigned int n, int start)
{
	int		count;

	count = 0;
	if (printf_puthex_aux(n, &count, start))
		return (-1);
	return (count);
}

int	printf_puthex_adrs(unsigned long n)
{
	int	count;

	count = 2;
	if (printf_putstr("0x") == -1)
		return (-1);
	if (printf_puthex_aux(n, &count, 'a'))
		return (-1);
	return (count);
}
