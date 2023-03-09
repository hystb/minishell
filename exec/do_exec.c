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


void	set_ret_code(char *code, t_data var_lst)
{
	t_env	*env;


	if (!code)
		write_error("Memory allocation error !");
	env = *var_lst.env_var;
	while (env)
	{
		if (ft_strnstr(env->name_var, "?", (ft_strlen("?") + 1)))
		{
			free(env->content_var);
			env->content_var = code;
		}
		env = env->next;
	}
}

void	wait_childs(t_listpids **pids, t_data var_lst)
{
	int			status;
	t_listpids	*old;

	while (*pids)
	{
		old = *pids;
		waitpid((*pids)->pid, &status, 0);
		*pids = (*pids)->next;
		free(old);
	}
	free(pids);
	if (WIFEXITED(status))
		set_ret_code(ft_itoa(WEXITSTATUS(status)), var_lst);
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
		make_pipe(lst_cmd, env, list_pids, &fd_old);
		wait_childs(list_pids, var_lst);
	}
	else
		set_ret_code(ft_itoa(130), var_lst);
	g_signal_handle = 0;
}
