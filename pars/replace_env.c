/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:12:25 by nmilan            #+#    #+#             */
/*   Updated: 2023/03/06 12:52:16 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_env_var(t_data var_lst)
{
	t_list	*tmp;
	int		i;
	char	*new_content;
	int		j;

	tmp = *var_lst.cmd_lst;
	j = 0;
	while (tmp)
	{
		i = 0;
		while (tmp->content != NULL && tmp->content[i])
		{
			new_content = is_env_vars(tmp->content[i], var_lst, j);
			if (new_content)
				tmp->content[i] = new_content;
			i++;
		}
		tmp = tmp->next;
	}
}

char	*is_env_vars(char *arg, t_data var_lst, int j)
{
	int		is_sp_quote;
	int		i;
	char	*var;

	is_sp_quote = 0;
	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '\'' && is_sp_quote == 0)
			is_sp_quote = 1;
		else if (arg[i] == '\'' && is_sp_quote == 1)
			is_sp_quote = 0;
		if (arg[i] == '$' && is_sp_quote == 0)
		{
			j = i + 1;
			while (arg[i] != ' ' && arg[i] != '\f' && arg[i] != '\n'
				&& arg[i] != '\t' && arg[i] != '\v' && arg[i] != '\r'
				&& arg[i] && arg[i] != '"')
				i++;
			var = ft_substr(arg, j, i - j);
			var = sub_env_var(var, arg, j - 1, var_lst);
			return (var);
		}
	}
	return (NULL);
}

char	*sub_env_var(char *var, char *arg, int start, t_data var_lst)
{
	char	*new_content;
	char	*new_arg;
	int		end;

	end = start + ft_strlen(arg);
	new_content = find_env_var(var, var_lst);
	if (!new_content)
	{
		free(var);
		return (NULL);
	}
	new_arg = ft_strjoin(ft_strjoin(ft_substr(arg, 0, start), new_content), \
	ft_substr(arg, end, ft_strlen(&var[end])));
	free(arg);
	free(var);
	return (new_arg);
}

char	*find_env_var(char *var, t_data var_lst)
{
	t_env	*env;

	env = *var_lst.env_var;
	while (env)
	{
		if (ft_strnstr(env->name_var, var, (ft_strlen(var) + 1)))
		{
			return (ft_strdup(env->content_var));
		}
		env = env->next;
	}
	return (NULL);
}
