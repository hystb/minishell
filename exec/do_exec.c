/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:39:23 by ebillon           #+#    #+#             */
/*   Updated: 2023/02/22 14:46:32 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

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
	if (WIFEXITED(status))
		printf("Voici la valeur de retour de l'exit : %d\n", WEXITSTATUS(status));
}

void	do_exec(t_list **lst_cmd, char **env)
{
	int			status;
	t_list		*temp;
	int		fd_old;

	t_listpids	**list_pids;
	list_pids = malloc(sizeof(t_listpids *));
	*list_pids = NULL;
	fd_old = 0;
	make_pipe(lst_cmd, env, list_pids, &fd_old);
	wait_childs(list_pids);
}
