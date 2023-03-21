/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:22:23 by nmilan            #+#    #+#             */
/*   Updated: 2023/03/21 12:33:06 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_env	*envnew(char *content, int end)
{
	t_env	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->name_var = ft_substr(content, 0, end);
	new->content_var = ft_substr(content, end + 1, ft_strlen(&content[end]));
	new->next = NULL;
	new->previous = NULL;
	return (new);
}

void	env_add_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	tmp = *lst;
	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->previous = tmp;
}

void	free_env_var(t_env **env)
{
	t_env	*tmp;
	t_env	*lst;

	if (!env)
		return ;
	lst = *env;
	while (lst)
	{
		tmp = lst->next;
		free(lst->name_var);
		free(lst->content_var);
		free(lst);
		lst = tmp;
	}
	free(env);
}

t_env	**put_env(char **envp, t_data var_lst)
{
	var_lst.env_var = make_env_in_lst(envp);
	if (!var_lst.env_var)
		exit(1);
	return (var_lst.env_var);
}

t_env	**make_env_in_lst(char **envp)
{
	int		i;
	int		j;
	t_env	**env_var;

	env_var = malloc(sizeof(t_env *));
	if (!env_var)
		return (NULL);
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
	env_add_back(env_var, envnew("?=0", 1));
	return (env_var);
}
