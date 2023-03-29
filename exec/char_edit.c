/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:56:09 by nmilan            #+#    #+#             */
/*   Updated: 2023/03/29 15:20:40 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*rechange_target(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == -6)
			str[i] = '<';
		if (str[i] == -7)
			str[i] = '>';
		i++;
	}
	return (str);
}

void	change_negative(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		rechange_target(tab[i]);
		i++;
	}
}

char	*realloc_sp_sign(char *input, char c, int i)
{
	char	*res;
	int		j;

	j = i + 1;
	res = malloc(sizeof(char) * (ft_strlen(input) + 3));
	if (!res)
		return (NULL);
	ft_strlcpy(res, input, i + 1);
	res[j - 1] = ' ';
	res[j++] = c;
	res[j++] = ' ';
	res[j] = '\0';
	ft_strlcpy(&res[j], &input[i + 1], ft_strlen(input));
	free(input);
	return (res);
}

char	*realloc_db_sign(char *input, char c, int i)
{
	char	*res;
	int		j;

	j = i + 1;
	res = malloc(sizeof(char) * (ft_strlen(input) + 4));
	if (!res)
		return (NULL);
	ft_strlcpy(res, input, i + 1);
	res[j - 1] = ' ';
	res[j++] = c;
	res[j++] = c;
	res[j++] = ' ';
	res[j] = '\0';
	ft_strlcpy(&res[j], &input[i + 2], ft_strlen(input));
	free(input);
	return (res);
}
