/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:52:06 by nmilan            #+#    #+#             */
/*   Updated: 2023/03/29 15:05:20 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	del_free_content(void **content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		free(content[i]);
		i++;
	}
	free(content);
}

void	free_pids(t_listpids **pids)
{
	t_listpids	*tmp;
	t_listpids	*old;

	if (!pids)
		return ;
	if (!*pids)
		return (free(pids));
	tmp = *pids;
	while (tmp)
	{
		old = tmp;
		tmp = tmp->next;
		free(old);
	}
	free(pids);
}

void	free_data(t_data data)
{
	free_pids(data.lst_pids);
	if (data.cmd_lst)
	{
		while ((*data.cmd_lst)->previous)
			(*data.cmd_lst) = (*data.cmd_lst)->previous;
		ft_lstclear(data.cmd_lst, del_free_content);
		free(data.cmd_lst);
	}
	free_env_var(data.env_var);
}

void	free_heredocs(t_list **cmds)
{
	t_list	*i;

	if (!cmds || !*cmds)
		return ;
	i = *cmds;
	while (i)
	{
		if (i->fd_heredoc)
			close(i->fd_heredoc);
		i = i->next;
	}
}
