/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 13:52:06 by nmilan            #+#    #+#             */
/*   Updated: 2023/03/21 14:46:14 by ebillon          ###   ########.fr       */
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
	t_listpids	*i;

	if (!pids)
		return ;
	i = *pids;
	while (i)
	{
		free(i);
		i = i->next;
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
