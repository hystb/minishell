/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:23:03 by nmilan            #+#    #+#             */
/*   Updated: 2023/03/28 13:09:21 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_quote(t_data var_lst)
{
	t_list	*tmp;
	int		i;
	char	*new_content;
	int		j;
	char	c;

	tmp = *var_lst.cmd_lst;
	c = 0;
	j = -1;
	while (tmp)
	{
		i = 0;
		while (tmp->content != NULL && tmp->content[i])
		{
			new_content = is_quote(tmp->content[i], j, c);
			tmp->content[i] = new_content;
			i++;
		}
		tmp = tmp->next;
	}
}

char	*is_quote(char *in, int i, char c)
{
	int		index;
	char	*tmp;

	while (in[++i])
	{
		if (in[i] == '\'' || in[i] == '"')
		{
			if (!c)
			{
				c = in[i];
				index = i;
			}
			else if (in[i] == c)
			{
				tmp = in;
				in = ft_strjoin(ft_substr(in, 0, index), \
				ft_strjoin(ft_substr(in, index + 1, i - 1 - index), \
				ft_substr(in, i + 1, ft_strlen(in))));
				free(tmp);
				c = 0;
				i = i - 2;
			}
		}
	}
	return (in);
}

void	restore_quote(t_data var_lst)
{
	t_list	*tmp;
	int		i;

	tmp = *var_lst.cmd_lst;
	while (tmp)
	{
		i = 0;
		while (tmp->content && tmp->content[i])
		{
			change_quote(tmp->content[i]);
			i++;
		}
		tmp = tmp->next;
	}
}

void	change_quote(char *in)
{
	int	i;

	i = 0;
	while (in && in[i])
	{
		if (in[i] == -3)
			in[i] = '\'';
		if (in[i] == -4)
			in[i] = '"';
		if (in[i] == -5)
			in[i] = '$';
		i++;
	}
}
