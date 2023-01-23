/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:49:52 by ebillon           #+#    #+#             */
/*   Updated: 2023/01/23 15:54:40 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

/* do the loop that execute and pipe the command, then return the fd filled */
void	redirect(char **cmds, int argc, char **env, int *fd, pid_t *gpid)
{
	int		tube[2];
	pid_t	pid;

	if (pipe(tube) == -1)
		exit_error();
	pid = fork();
	if (pid == -1)
		exit_error();
	if (pid == 0)
		do_child(tube, cmds, env);
	else
	{
		close(tube[1]);
		if (argc > 1)
		{
			dup2(tube[0], STDIN_FILENO);
			close(tube[0]);
			redirect(++cmds, argc - 1, env, fd, gpid);
		}
		else
		{
			*fd = tube[0];
			*gpid = pid;
		}
	}
}

/* change here by passing the cmd */
void	do_child(int *tube, char **cmds, char **env)
{
	if (dup2(tube[1], STDOUT_FILENO) == -1)
		exit_error();
	do_execute(ft_split(*cmds, ' '), env, tube);
}

/* do the command */
void	do_execute(char **args, char **env, int *tube)
{
	char	*cmd;

	if (access(cmd, O_RDONLY) == -1)
		cmd = get_path(*args, env);
	else
		cmd = ft_strdup(*args);
	close(tube[0]);
	if (cmd)
	{
		if (execve(cmd, args, env) == -1)
			exit_error();
	}
	else
		not_found_error(*args);
	close(tube[1]);
	free(cmd);
	free(args);
}
