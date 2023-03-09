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

void	wait_childs(t_listpids **pids)
{
	int			status;
	t_listpids	*old;

	while (*pids)
	{
		old = *pids;
		waitpid((*pids)->pid, &status, 0);
		// printf("je viens d'attendre %d\n", (*pids)->pid);
		*pids = (*pids)->next;
		free(old);
	}
	free(pids);
	// if (WIFEXITED(status))
	// 	printf("Voici la valeur de retour de l'exit : %d\n", WEXITSTATUS(status));
}

void	do_heredocs(t_list **lst_cmd)
{
	t_list	*temp;

	temp = *lst_cmd;
	while (temp)
	{
		temp->fd_heredoc = 0;
		make_redir_inside_aux(temp, &temp->fd_heredoc);
		temp = temp->next;
	}
}

void	do_exec(t_list **lst_cmd, char **env)
{
	int			fd_old;

	if (!(*lst_cmd)->content[0])
		return ;
	t_listpids	**list_pids;
	list_pids = malloc(sizeof(t_listpids *));
	*list_pids = NULL;
	fd_old = 0;
	g_signal_handle = 1;
	do_heredocs(lst_cmd);
	make_pipe(lst_cmd, env, list_pids, &fd_old);
	wait_childs(list_pids);
	g_signal_handle = 0;
}
