/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 16:01:15 by nmilan            #+#    #+#             */
/*   Updated: 2023/03/27 17:41:42 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_var(char *arg, t_data var_lst, int j, int i)
{
	char	*var;

	if (i == j)
	{
		var = malloc(sizeof(char) * 2);
		if (!var)
			return (NULL);
		var[0] = -5;
		var[1] = '\0';
	}
	else
		var = ft_substr(arg, j, i - j);
	var = sub_env_var(var, arg, j - 1, var_lst);
	return (var);
}

int	end_env(int start, char *arg)
{
	start++;
	while (arg[start] && arg[start] != ' '
		&& arg[start] != '\'' && arg[start] != '"' && arg[start] != '$')
	{
		start++;
	}
	return (start);
}

void	is_env_synthax(char *in, int j, int *i)
{
	int	have_alpha;

	have_alpha = 0;
	while (in && in[*i])
	{	
		if (*i == j && in[*i] == '?')
		{
			*i = *i + 1;
			return ;
		}
		else if (*i == j && ft_isdigit(in[*i]))
			*i = *i + 1;
		else if (ft_isdigit(in[*i]) && have_alpha)
			*i = *i + 1;
		else if (ft_isdigit(in[*i]))
			return ;
		else if (ft_isalpha(in[*i]) || in[*i] == '_')
		{
			*i = *i + 1;
			have_alpha = 1;
		}
		else
			return ;
	}
}
