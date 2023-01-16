/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:09:53 by ebillon           #+#    #+#             */
/*   Updated: 2022/11/11 11:09:55 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Function who remove all of the caracters at the begging and the end of *s
which are present in *set. Return the trimmed string in a allocate var.
*/

static int	is_in(const char *str, char e)
{
	while (*str)
	{
		if (e == *str++)
			return (1);
	}
	return (0);
}

static int	get_start(char const *s1, char const *set)
{
	int	count;

	count = 0;
	while (*s1 && is_in(set, *s1++))
		count++;
	return (count);
}

static int	get_end(char const *s1, char const *set)
{
	int		count;
	size_t	i;

	count = 0;
	i = ft_strlen(s1) - 1;
	while (i > 0 && (is_in(set, s1[i])))
	{
		i--;
		count++;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		lenght;
	char	*res;

	if (!s1 || !set)
		return (NULL);
	lenght = ft_strlen(s1) - get_start(s1, set) - get_end(s1, set);
	if (lenght <= 0)
	{
		return (ft_substr(s1, 0, 0));
	}
	res = ft_substr(s1, get_start(s1, set), lenght);
	return (res);
}
