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

void	read_result(int fd)
{
	char buff[2];

	if (fd > 0)
	{
		while (read(fd, buff, 1))
			write(1, buff, 1);
		close_fd(fd);
	}
}

void	do_exec(t_list **lst_cmd, char **env)
{
	t_redirect	data;
	int			status;

	data.fd = -1;
	data.tube_out = -1;
	data.pid = -1;
	// printf("le nombre de commandes -> %d\n", ft_lstsize(*lst_cmd));
	pre_redirect(*lst_cmd, ft_lstsize(*lst_cmd), env, &data);
	// wait(NULL);
	// printf("le pid %d\n", data.pid);
	waitpid(data.pid, &status, 0);
	read_result(data.fd);
}

// void	do_commands(char **cmds, char **env)
// {
// 	// int			status;
// 	// t_redirect  data;

// 	(void) cmds;
// 	(void) env;
// 	data.fd = -1;
// 	// data.tube_out = -1;
// 	// pre_redirect(cmds, 3, env, &data);
// 	// printf("pid: %d | fd: %d \n", data.pid, data.fd);
// 	// waitpid(data.pid, &status, 0);

// }
