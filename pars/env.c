/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:12:25 by nmilan            #+#    #+#             */
/*   Updated: 2023/02/22 13:56:32 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



t_env	**put_env(char **envp, t_data var_lst)
{
	t_list	*tmp;
	int		i;
	t_env	*env;

	tmp = *var_lst.cmd_lst;
	var_lst.env_var = make_env_in_lst(envp, tmp);
	env = *var_lst.env_var;
	return (var_lst.env_var);
}

char	*is_env_vars(char *arg)
{
	int		is_sp_quote;
	int		i;
	char	*var;
	int		j;

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
			sub_env_var(var, arg, j - 1, i - j);
			return (var);
		}
	}
}

void	sub_env_var(char *var, char *arg, int start, int size)
{
	
}

t_env	**make_env_in_lst(char **envp, t_list *cmd)
{
	int		i;
	int		j;
	t_env	**env_var;

	env_var = malloc(sizeof(t_env *));
	if (!env_var)
	{
		//add malloc protect
	}
	*env_var = NULL;
	i = 0;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
		{
			j++;
		}
		env_add_back(env_var, envnew(envp[i], j));
		i++;
	}
	return (env_var);
}
