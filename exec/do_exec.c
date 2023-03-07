/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:39:23 by ebillon           #+#    #+#             */
/*   Updated: 2023/03/07 14:09:35 by ebillon          ###   ########.fr       */
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
		*pids = (*pids)->next;
		free(old);
	}
	free(pids);
	// if (WIFEXITED(status))
	// 	printf("Voici la valeur de retour de l'exit : %d\n", WEXITSTATUS(status));
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
	make_pipe(lst_cmd, env, list_pids, &fd_old);
	wait_childs(list_pids);
	g_signal_handle = 0;
}
