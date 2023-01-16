/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:21:03 by ebillon           #+#    #+#             */
/*   Updated: 2022/11/14 15:21:07 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Integer to Ascii, allocate the returned value.
Return NULL if error.
*/

static int	getsize(long int nbr)
{
	long int	size;
	int			count;

	count = 0;
	size = 1;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
	{
		nbr *= -1;
		count++;
	}
	while (size <= nbr)
	{
		size *= 10;
		count++;
	}
	return (count);
}

static void	rev_in_tab(char *tab, int size)
{
	int		i;
	char	temp;

	i = 0;
	while (i < size + 1 / 2)
	{
		temp = tab[i];
		tab[i] = tab[size];
		tab[size] = temp;
		i++;
		size--;
	}
}

char	*ft_itoa(int n)
{
	char		*res;
	long int	nbr;
	int			i;

	i = 0;
	nbr = n;
	res = ft_calloc(getsize(nbr) + 1, sizeof(char));
	if (!res)
		return (NULL);
	if (nbr < 0)
		nbr *= -1;
	if (n == 0)
		res[i++] = '0';
	while (nbr > 0)
	{
		res[i++] = (int)((nbr % 10) + 48);
		nbr = nbr / 10;
	}
	if (n < 0)
		res[i++] = '-';
	res[i] = '\0';
	rev_in_tab(res, ft_strlen(res) - 1);
	return (res);
}
