/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_commands.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:49:01 by ebillon           #+#    #+#             */
/*   Updated: 2023/01/23 15:59:23 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	do_commands(char **commands, char **env)
{
	/* */
}

/* write in a file (create it if does not exist) 
*	if mode == 1 -> append mode
*	else -> overwrite mode
*/
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