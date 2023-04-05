/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:22:39 by nmilan            #+#    #+#             */
/*   Updated: 2023/04/03 14:32:34 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*control_pipe(char *in, int i)
{
	int		is_write;
	char	c;

	c = 0;
	while (in && in[i])
	{
		c = is_quote_in_sign(c, in[i]);
		if (in[i] == '|' && c == 0)
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

char	*empty_before_pipe(char *in, int i, int is_content)
{
	while (in && in[i])
	{
		if (in[i] == '|' && is_content == 0)
		{
			free(in);
			ft_putstr_fd(PIPE_ERROR, 2);
			return (NULL);
		}
		if (in[i] != ' ')
			is_content = 1;
		i++;
	}
	return (in);
}

char	*replace_tab_and_printable(char *in)
{
	int		i;
	char	c;

	i = 0;
	c = 0;
	while (in && in[i])
	{
		if ((in[i] == '"' || in[i] == '\'') && c == 0)
			c = in[i];
		else if (in[i] == c && c != 0)
			c = 0;
		if (in[i] < 0 || in[i] >= 127)
		{
			free(in);
			return (NULL);
		}
		if (in[i] == '\t' && c == 0)
			in[i] = ' ';
		i++;
	}
	return (in);
}
