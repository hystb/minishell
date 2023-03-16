/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethaaalpha <ethaaalpha@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:39:23 by ebillon           #+#    #+#             */
/*   Updated: 2023/03/16 15:44:36 by ethaaalpha       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/gnl.h"

unsigned int	next_line_len(char *buffer)
{
	unsigned int	i;

	i = 0;
	while (buffer[i] != '\n')
	{
		if (buffer[i] == '\0')
		{
			return (i);
		}
		i++;
	}
	return (i);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	const char	*str_src;
	char		*str_dst;

	if (!dst && !src)
		return (dst);
	str_dst = dst;
	str_src = src;
	if (str_dst < str_src)
	{
		while (len-- > 0)
			*str_dst++ = *str_src++;
		*str_dst = '\0';
	}
	else
	{
		str_src = src + (len - 1);
		str_dst = dst + (len);
		*str_dst-- = '\0';
		while (len-- > 0)
			*str_dst-- = *str_src--;
	}
	return (dst);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	int		i;
	int		pos;
	char	*tab;

	if (!s1)
		return (NULL);
	if (!s2)
	{
		free(s1);
		return (NULL);
	}
	tab = malloc(sizeof(char) * (gnl_strlen(s1) + gnl_strlen(s2) + 1));
	if (!(tab))
		return (NULL);
	i = 0;
	pos = 0;
	while (s1[i] != '\0')
		tab[pos++] = s1[i++];
	i = 0;
	while (s2[i] != '\0')
		tab[pos++] = s2[i++];
	tab[pos] = '\0';
	free(s1);
	free(s2);
	return (tab);
}

size_t	gnl_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}
