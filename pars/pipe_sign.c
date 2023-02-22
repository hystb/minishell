/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_sign.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 15:41:50 by nmilan            #+#    #+#             */
/*   Updated: 2023/02/22 15:12:50 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*add_pipe_sign(char *input)
{
	int		i;
	int		found_pipe;

	i = 0;
	found_pipe = 0;
	if (need_pipe(input))
		return (input);
	while (input[i])
	{
		if (input[i] == '|')
			found_pipe = 1;
		if ((input[i] == '<' || input[i] == '>') && found_pipe == 1)
		{
			input = add_pipe(input, i);
			i = i + 4;
		}
		i++;
	}
	return (input);
}

int	need_pipe(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '<' || input[i] == '>')
			return (0);
		i++;
	}
	return (1);
}

char	*add_pipe(char *input, int i)
{
	char	*res;
	int		j;

	j = i + 1;
	res = malloc(sizeof(char) * (ft_strlen(input) + 4));
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
	ft_strlcpy(&res[j], &input[i], (ft_strlen(input) + 4));
	free(input);
	return (res);
}
