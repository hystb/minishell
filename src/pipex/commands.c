/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:49:01 by ebillon           #+#    #+#             */
/*   Updated: 2023/01/24 16:56:39 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

/* write in a file (create it if does not exist) 
*	if mode == 1 -> append mode
*	else -> overwrite mode
*/

void	do_commands(char **cmds, char **env)
{
	int	fd = 2;
	int len = 1;
	pid_t	gpid;
	
	redirect(cmds, 2, env, &fd, &gpid);
	char buff[2];
	// printf("%d\n", gpid);
	while (read(fd, buff, 1))
		write(1, buff, 1);
	close(fd);
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
