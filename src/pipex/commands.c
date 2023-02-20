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
	int			status;
	t_redirect  data;

	data.fd = -1;
	// data.tube_out = -1;
	pre_redirect(cmds, 3, env, &data);
	// printf("pid: %d | fd: %d \n", data.pid, data.fd);
	waitpid(data.pid, &status, 0);
	char buff[2];
	if (data.fd > 0)
	{
		while (read(data.fd, buff, 1))
			write(1, buff, 1);
		close(data.fd);
	}
}
