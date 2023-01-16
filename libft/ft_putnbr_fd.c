/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:02:21 by ebillon           #+#    #+#             */
/*   Updated: 2022/11/14 18:02:22 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Write the number n on the fd.
*/

void	ft_putnbr_fd(int n, int fd)
{
	long int	nbr;

	nbr = n;
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		nbr *= -1;
	}
	if (nbr > 9)
	{
		ft_putnbr_fd(nbr / 10, fd);
		ft_putchar_fd(nbr % 10 + '0', fd);
	}
	else
		ft_putchar_fd(nbr + '0', fd);
}
