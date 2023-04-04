/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:39:23 by ebillon           #+#    #+#             */
/*   Updated: 2023/04/04 11:12:14 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_childs(t_listpids **pids, t_data var_lst)
{
	t_listpids	*tmp;
	int			status;

	tmp = *pids;
	if (!tmp)
		return ;
	while (tmp)
	{
		waitpid(tmp->pid, &status, 0);
		tmp = tmp->next;
	}
	if (WIFEXITED(status))
		set_value_env("?", ft_itoa(WEXITSTATUS(status)), var_lst);
}

void	put_heredocs_val(t_list **list_cmd)
{
	t_list	*cmds;

	cmds = *list_cmd;
	while (cmds)
	{
		cmds->fd_heredoc = 0;
		cmds = cmds->next;
	}
}

int	do_heredocs(t_list **lst_cmd, t_data data, int val)
{
	t_list	*temp;

	temp = *lst_cmd;
	put_heredocs_val(lst_cmd);
	while (temp)
	{
		make_redir_inside_aux(temp, &temp->fd_heredoc, data);
		wait(NULL);
		if (temp->fd_heredoc == -130)
		{
			val++;
			break ;
		}
		temp = temp->next;
	}
	if (val)
	{
		while (temp)
		{
			if (temp->fd_heredoc && temp->fd_heredoc != -130)
				close(temp->fd_heredoc);
			temp = temp->previous;
		}
	}
	return (val);
}

t_listpids	**malloc_pids(t_data var_lst)
{
	t_listpids	**list_pids;

	list_pids = malloc(sizeof(t_listpids *));
	if (!list_pids)
		write_error("Memory allocation error !", var_lst);
	*list_pids = NULL;
	return (list_pids);
}

void	do_exec(t_data var_lst, t_list **lst_cmd, int fd_old, t_list *tmp)
{
	t_listpids	**list_pids;

	if (!*lst_cmd || !(*lst_cmd)->content[0]
		|| is_blank((*lst_cmd)->content[0]))
		return ;
	tmp = *lst_cmd;
	list_pids = malloc_pids(var_lst);
	g_signal_handle = 1;
	if (!do_heredocs(lst_cmd, var_lst, 0))
	{
		if (!(*lst_cmd)->next)
		{
			if (make_only(var_lst, list_pids, &fd_old))
				set_value_env("?", ft_strdup("1"), var_lst);
		}
		else
			make_pipe(var_lst, list_pids, &fd_old);
		wait_childs(list_pids, var_lst);
	}
	else
		set_value_env("?", ft_strdup("130"), var_lst);
	free_pids(list_pids);
	*lst_cmd = tmp;
	g_signal_handle = 0;
}
