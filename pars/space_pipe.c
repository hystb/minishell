/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:51:19 by nmilan            #+#    #+#             */
/*   Updated: 2023/03/29 13:53:48 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*add_space_pipe(char *input)
{
	int		i;

	i = 0;
	while (input && input[i])
	{
		if (input[i] == '|')
		{
			input = realloc_input(input, i);
			i++;
		}
		if (input[i])
			i++;
	}
	return (space_sign(input, 0));
}

int	need_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (i > 0 && input[i] == '|' && (input[i - 1] != ' '
				|| input[i + 1] != ' '))
			return (0);
		if (input[i] == '$')
			return (0);
		i++;
	}
	return (1);
}

char	*realloc_input(char *input, int i)
{
	char	*res;
	int		j;

	j = i + 1;
	res = malloc(sizeof(char) * (ft_strlen(input) + 3));
	if (!res)
		return (NULL);
	ft_strlcpy(res, input, i + 1);
	res[j - 1] = ' ';
	res[j++] = '|';
	res[j++] = ' ';
	res[j] = '\0';
	ft_strlcpy(&res[j], &input[i + 1], ft_strlen(input));
	free(input);
	return (res);
}

char	*space_sign(char *input, int i)
{
	char	c;

	c = 0;
	while (input && input[i])
	{
		if (input[i] == '<' || input[i] == '>')
		{
			c = input[i];
			i++;
			if (c != 0 && input[i] == c)
			{
				input = realloc_db_sign(input, c, i - 1);
				i = i + 2;
			}
			else
			{
				input = realloc_sp_sign(input, c, i - 1);
				i++;
			}
		}
		else
			i++;
	}
	return (input);
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
