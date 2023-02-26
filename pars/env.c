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



void	put_env(char **envp, t_list *cmd)
{
	t_list	*tmp;
	int		i;

	tmp = cmd;
	cmd->env_var = make_env_in_lst(envp, cmd);
	while (cmd->env_var)
	{
		ft_printf("name : %s\ncontent : %s\n", cmd->env_var->name_var, cmd->env_var->content_var);
		cmd->env_var = cmd->env_var->next;
	}
	i = 0;
	while (tmp)
	{
		while (tmp->content[i])
		{
			//is_env_vars(tmp->content[i]);
			i++;
		}
		tmp = tmp->next;
	}
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

t_env	*make_env_in_lst(char **envp, t_list *cmd)
{
	int		i;
	int		j;
	t_env	**env_var;
	t_env	*env;

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
		make_node_env(envp[i], j, env_var);
		i++;
	}
	env = *env_var;
	free(env_var);
	return (env);
}

void	make_node_env(char *env, int split, t_env **env_var)
{
	/*if (!env_var)
	{
		env_var = envnew(env, split);
		return ;
	}*/
	env_add_back(env_var, envnew(env, split));
}