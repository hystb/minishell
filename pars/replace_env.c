/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:12:25 by nmilan            #+#    #+#             */
/*   Updated: 2023/03/07 14:24:20 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_env_var(t_data var_lst)
{
	t_list	*tmp;
	int		i;
	char	*new_content;
	int		j;
	int		k;

	tmp = *var_lst.cmd_lst;
	j = 0;
	k = -1;
	while (tmp)
	{
		i = 0;
		while (tmp->content != NULL && tmp->content[i])
		{
			new_content = is_env_vars(tmp->content[i], var_lst, j, k);
			if (new_content)
				tmp->content[i] = new_content;
			i++;
		}
		tmp = tmp->next;
	}
	replace_quote(var_lst);
}

char	*is_env_vars(char *arg, t_data var_lst, int j, int i)
{
	int		is_sp_quote;
	char	*var;

	is_sp_quote = 0;
	while (arg[++i])
	{
		if (arg[i] == '"' && is_sp_quote == 0)
			is_sp_quote = 3;
		else if (arg[i] == '"' && is_sp_quote == 3)
			is_sp_quote = 0;
		if (arg[i] == '\'' && is_sp_quote == 0)
			is_sp_quote = 1;
		else if (arg[i] == '\'' && is_sp_quote == 1)
			is_sp_quote = 0;
		if (arg[i] == '$' && (is_sp_quote == 0 || is_sp_quote == 3))
		{
			j = i + 1;
			while (arg[i] != ' ' && arg[i] && arg[i] != '"' && arg[i] != '\'')
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

	end = end_env(start, arg);
	new_content = find_env_var(var, var_lst);
	if (!new_content)
	{
		free(var);
		return (NULL);
	}
	new_arg = ft_strjoin(ft_strjoin(ft_substr(arg, 0, start), new_content), \
	ft_substr(arg, end, ft_strlen(arg)));
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
