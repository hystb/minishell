/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:12:25 by nmilan            #+#    #+#             */
/*   Updated: 2023/03/29 15:13:14 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	replace_env_var(t_data var_lst)
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
			new_content = is_env_vars(tmp->content[i], var_lst, 0, -1);
			if (new_content)
				tmp->content[i] = new_content;
			i++;
		}
		if (!new_content)
			tmp = tmp->next;
	}
	replace_quote(var_lst);
	restore_quote(var_lst);
	split_env(var_lst);
}

char	*is_env_vars(char *arg, t_data var_lst, int j, int i)
{
	int		is_sp_quote;

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
			i++;
			is_env_synthax(arg, j, &i);
			return (get_var(arg, var_lst, j, i));
		}
	}
	return (NULL);
}

char	*sub_env_var(char *var, char *arg, int start, t_data var_lst)
{
	char	*new_content;
	char	*new_arg;
	int		end;

	if (!var)
		return (NULL);
	end = start + 1;
	is_env_synthax(arg, start + 1, &end);
	if (var[0] != -5)
		new_content = find_env_var(var, var_lst, 0);
	else
		new_content = ft_strdup(var);
	new_arg = ft_strjoin(ft_strjoin(ft_substr(arg, 0, start), new_content), \
	ft_substr(arg, end, ft_strlen(arg)));
	if (!new_arg)
		new_arg = ft_strdup("\0");
	free(arg);
	free(var);
	if (!new_arg)
		return (NULL);
	return (new_arg);
}

char	*find_env_var(char *var, t_data var_lst, int i)
{
	t_env	*env;
	char	*res;

	env = *var_lst.env_var;
	res = NULL;
	while (env)
	{
		if (ft_strnstr(env->name_var, var, (ft_strlen(env->name_var))))
		{
			i = 0;
			res = ft_strdup(env->content_var);
			while (res && res[i])
			{
				if (res[i] == '\'')
					res[i] = -3;
				if (res[i] == '"')
					res[i] = -4;
				if (res[i] == ' ')
					res[i] = -8;
				i++;
			}
		}
		env = env->next;
	}
	return (res);
}
