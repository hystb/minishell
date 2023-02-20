/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:51:19 by nmilan            #+#    #+#             */
/*   Updated: 2023/01/30 16:35:36 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*add_space_pipe(char *input)
{
	int		i;

	i = 0;
	if (need_space(input))
		return (input);
	while (input[i])
	{
		if (input[i] == '|')
		{
			input = realloc_input(input, i);
			i++;
		}
		i++;
	}
	return (input);
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
	{
		//error to put
		exit (1);
	}
	ft_strlcpy(res, input, i + 1);
	res[j - 1] = ' ';
	res[j++] = '|';
	res[j++] = ' ';
	res[j] = '\0';
	ft_strlcpy(&res[j], &input[i + 1], ft_strlen(input));
	free(input);
	return (res);
}
