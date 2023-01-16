/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 11:10:01 by ebillon           #+#    #+#             */
/*   Updated: 2022/11/11 11:10:03 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Split a string delimited by c, return a **tab full allocated of the \
differents strings. The **tab is terminated by NULL.
*/

static int	res_size(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	if (!*s)
		return (0);
	while (s[i])
	{
		if (s[i] == c)
		{
			count++;
			while (s[i] == c)
				i++;
		}
		i++;
	}
	return (count);
}

static int	word_size(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != c && s[i])
	{
		i++;
		count++;
	}
	return (count);
}

static char	**error_malloc(char **res, char *str)
{
	int	i;

	i = 0;
	while (res[i] != NULL)
	{
		free(res[i]);
		i++;
	}
	free(res);
	free(str);
	return (NULL);
}

static char	**ft_split_aux(char c, int j, char *str)
{
	char	**res;
	char	*part;
	int		rsize;
	int		i;

	i = 0;
	rsize = res_size(str, c);
	res = ft_calloc(rsize + 1, sizeof(char *));
	if (!res)
		return (error_malloc(res, str));
	while (rsize--)
	{
		part = ft_calloc(word_size(&str[i], c) + 1, sizeof(char));
		if (!part)
			return (error_malloc(res, str));
		ft_strlcpy(part, &str[i], word_size(&str[i], c) + 1);
		res[j++] = part;
		i = i + word_size(&str[i], c);
		while (str[i] == c)
			i++;
	}
	res[j] = NULL;
	free(str);
	return (res);
}

char	**ft_split(char const *s, char c)
{
	char	set[2];
	char	*str;
	int		j;

	if (!s)
		return (0);
	j = 0;
	set[0] = c;
	set[1] = '\0';
	str = ft_strtrim(s, set);
	if (!str)
		return (NULL);
	return (ft_split_aux(c, j, str));
}
