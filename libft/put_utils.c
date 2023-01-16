/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:30:27 by ebillon           #+#    #+#             */
/*   Updated: 2023/01/16 13:34:07 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printf_putchar(char c)
{
	return (write(1, &c, 1));
}

int	printf_putstr(char *c)
{
	int	size;

	size = 0;
	if (!c)
		return (printf_putstr("(null)"));
	while (*c)
	{
		if (printf_putchar(*c++) == -1)
			return (-1);
		size++;
	}
	return (size);
}

int	printf_putnbr_aux(long nbr, int *count)
{
	if (nbr < 0)
	{
		if (printf_putchar('-') == -1)
			return (-1);
		*count += 1;
		nbr *= -1;
	}
	if (nbr > 9)
	{
		if (printf_putnbr_aux(nbr / 10, count) == -1)
			return (-1);
		if (printf_putchar(nbr % 10 + '0') == -1)
			return (-1);
		*count += 1;
	}
	else
	{
		if (printf_putchar(nbr + '0') == -1)
			return (-1);
		*count += 1;
	}
	return (0);
}

int	printf_putnbr(long n)
{
	int	count;

	count = 0;
	if (printf_putnbr_aux(n, &count) == -1)
		return (-1);
	return (count);
}
