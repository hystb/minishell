/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:39:23 by ebillon           #+#    #+#             */
/*   Updated: 2023/02/20 15:46:06 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
	// void	pre_redirect(char **cmds, int argc, char **env, t_redirect *data)

void	do_exec(t_list **lst_cmd, char **env)
{
	t_redirect	data;

	data.fd = -1;
	data.tube_out = -1;
	data.pid = -1;
	pre_redirect(*lst_cmd, ft_lstsize(*lst_cmd), env, &data);
	// lire dans le tube de sortie.
}

void	do_commands(char **cmds, char **env)
{
	// int			status;
	t_redirect  data;

	(void) cmds;
	(void) env;
	data.fd = -1;
	// data.tube_out = -1;
	// pre_redirect(cmds, 3, env, &data);
	// printf("pid: %d | fd: %d \n", data.pid, data.fd);
	//waitpid(data.pid, &status, 0);
	char buff[2];
	if (data.fd > 0)
	{
		while (read(data.fd, buff, 1))
			write(1, buff, 1);
		close(data.fd);
	}
}
