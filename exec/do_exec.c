/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:39:23 by ebillon           #+#    #+#             */
/*   Updated: 2023/03/21 14:57:54 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	wait_childs(t_listpids **pids, t_data var_lst)
{
	t_listpids	*tmp;
	int			status;

	tmp = *pids;
	while (tmp)
	{
		waitpid(tmp->pid, &status, 0);
		tmp = tmp->next;
	}
	if (WIFEXITED(status))
		set_value_env("?", ft_itoa(WEXITSTATUS(status)), var_lst);
}

int	do_heredocs(t_list **lst_cmd, t_data data)
{
	t_list	*temp;
	int		val;

	val = 0;
	temp = *lst_cmd;
	while (temp)
	{
		temp->fd_heredoc = 0;
		make_redir_inside_aux(temp, &temp->fd_heredoc, data);
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

	if (!(*lst_cmd)->content[0] || !*lst_cmd)
		return ;
	tmp = *lst_cmd;
	list_pids = malloc_pids(var_lst);
	g_signal_handle = 1;
	if (!do_heredocs(lst_cmd, var_lst))
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
