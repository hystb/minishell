/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:22:39 by nmilan            #+#    #+#             */
/*   Updated: 2023/03/27 16:33:11 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*control_pipe(char *in, int i)
{
	int	is_write;

	while (in && in[i])
	{
		if (in[i] == '|')
		{
			i++;
			is_write = 0;
			while (in[i] && in[i] != '|')
			{
				if (in[i] != ' ')
					is_write++;
				i++;
			}
			i--;
			if (is_write == 0)
			{
				free(in);
				ft_putstr_fd(PIPE_ERROR, 2);
				return (NULL);
			}
		}
		i++;
	}
	return (in);
}

char	*replace_tab_and_printable(char *in)
{
	int	i;

	i = 0;
	while (in && in[i])
	{
		if (in[i] < 20 || in[i] >= 127)
		{
			free(in);
			return (NULL);
		}
		if (in[i] == '	')
			in[i] = ' ';
		i++;
	}
	return (in);
}
