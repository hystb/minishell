/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:23:03 by nmilan            #+#    #+#             */
/*   Updated: 2023/03/07 14:30:04 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_quote(t_data var_lst)
{
	t_list	*tmp;
	int		i;
	char	*new_content;

	tmp = *var_lst.cmd_lst;
	while (tmp)
	{
		i = 0;
		while (tmp->content != NULL && tmp->content[i])
		{
			new_content = is_quote(tmp->content[i]);
			if (new_content)
			{
				free(tmp->content[i]);
				tmp->content[i] = new_content;
			}
			i++;
		}
		tmp = tmp->next;
	}
}

char	*is_quote(char *in)
{
	char	c;
	int		i;
	int		index;

	c = 0;
	i = 0;
	index = 0;
	while (in[i])
	{
		if (in[i] == '\'' || in[i] == '"')
		{
			if (!c)
			{
				c = in[i];
				index = i;
			}
			else if (in[i] == c)
				return (ft_strjoin(ft_substr(in, 0, index), \
				ft_strjoin(ft_substr(in, index + 1, i - 1), \
				ft_substr(in, i + 1, ft_strlen(&in[i + 1])))));
		}
		i++;
	}
	return (NULL);
}
