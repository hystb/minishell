/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:39:23 by ebillon           #+#    #+#             */
/*   Updated: 2023/03/07 14:33:41 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/minishell.h"


char	*get_item_env(t_data data, char *key)
{
	t_env	*env;

	env = *data.env_var;
	while (env)
	{
		if (ft_strnstr(env->name_var, key, (ft_strlen(key) + 1)))
		{
			return (env->content_var);
		}
		env = env->next;
	}
	return (NULL);
}

void	set_value_env(char *key, char *value, t_data var_lst)
{
	t_env	*env;


	if (!value)
		write_error("Memory allocation error !");
	env = *var_lst.env_var;
	while (env)
	{
		if (ft_strnstr(env->name_var, key, (ft_strlen(key) + 1)))
		{
			free(env->content_var);
			env->content_var = value;
		}
		env = env->next;
	}
}

void	wait_childs(t_listpids **pids, t_data var_lst)
{
	int			status;
	t_listpids	*old;

	if (!*pids)
		return (free(pids));
	while (*pids)
	{
		old = *pids;
		waitpid((*pids)->pid, &status, 0);
		*pids = (*pids)->next;
		free(old);
	}
	free(pids);
	if (WIFEXITED(status))
		set_value_env("?", ft_itoa(WEXITSTATUS(status)), var_lst);
}

int	do_heredocs(t_list **lst_cmd)
{
	t_list	*temp;
	int		val;

	val = 0;
	temp = *lst_cmd;
	while (temp)
	{
		temp->fd_heredoc = 0;
		make_redir_inside_aux(temp, &temp->fd_heredoc);
		if (temp->fd_heredoc == -130)
			val++;
		temp = temp->next;
	}
	temp = *lst_cmd;
	if (val)
	{
		while (temp)
		{
			if (temp->fd_heredoc)
				close(temp->fd_heredoc);
			temp = temp->previous;
		}
		return (1);
	}
	return (0);
}

void	do_exec(t_data var_lst, char **env)
{
	t_list		**lst_cmd;
	int			fd_old;

	lst_cmd = var_lst.cmd_lst;
	if (!(*lst_cmd)->content[0])
		return ;
	t_listpids	**list_pids;
	list_pids = malloc(sizeof(t_listpids *));
	*list_pids = NULL;
	fd_old = 0;
	g_signal_handle = 1;
	if (!do_heredocs(lst_cmd))
	{
		make_pipe(var_lst, env, list_pids, &fd_old);
		wait_childs(list_pids, var_lst);
	}
	else
		set_value_env("?", ft_itoa(130), var_lst);
	g_signal_handle = 0;
}
