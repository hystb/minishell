/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:49:01 by ebillon           #+#    #+#             */
/*   Updated: 2023/01/30 15:07:18 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

/* write in a file (create it if does not exist) 
*	if mode == 1 -> append mode
*	else -> overwrite mode
*/

void	do_commands(char **cmds, char **env)
{
	int 		len = 1;
	int			status;
	t_redirect  data;

	data.fd = -1;
	// data.tube_out = -1;
	// printf("fd %d", data.fd);
	pre_redirect(cmds, 5, env, &data);
	printf("pid: %d | fd: %d \n", data.pid, data.fd);
	// redirect(cmds, 3, env, data);
	waitpid(data.pid, &status, 0);
	char buff[2];
	if (data.fd > 0)
	{
		while (read(data.fd, buff, 1))
			write(1, buff, 1);
		close(data.fd);
	}
}

void	write_infile(int fd_in, char *out, int mode)
{
	char	buff[1];
	int		fd_out;

	if (mode == 1)
		fd_out = open(out, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd_out = open(out, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_out == -1)
		exit_error();
	while (read(fd_in, buff, 1))
		write(fd_out, buff, 1);
	close(fd_in);
	close(fd_out);
}
