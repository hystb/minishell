/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:49:52 by ebillon           #+#    #+#             */
/*   Updated: 2023/01/30 13:50:23 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

/* check about parent activity and redirections possibilites */
void	pre_redirect(char **cmds, int argc, char **env, t_redirect *data)
{
	printf("%s\n", cmds[0]);
	if (do_redirection(ft_split(*cmds, ' ')))
	{
		argc--;
		if (argc >= 1)
			redirect(++cmds, argc, env, data);
	}
	else
		redirect(cmds, argc, env, data);
}

/* do the loop that execute and pipe the command, then return the fd filled */
void	redirect(char **cmds, int argc, char **env, t_redirect *data)
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
			pre_redirect(++cmds, argc - 1, env, data);
		}
		else
			fill_redirect(tube[0], pid, data);
	}
}

void	fill_redirect(int fd, pid_t pid, t_redirect *data)
{
	data->fd = fd;
	data->pid = pid;
}

int	do_redirection(char **cmds)
{
	printf("%s\n", cmds[0]);
	if (ft_strncmp(cmds[0], "<", 1) == 0)
	{
		// printf("je suis une input < \n");
		do_input(cmds[1]);
		return (1);
	}
	// else if (ft_strncmp(cmds[0], "<<", 2) == 0)
		// printf("je suis un heredoc < \n");
	return (0);
}

// go and make the redirection ( mettre en place les buildints ici aussi) passer a la commande suivante si echec
/* change here by passing the cmd */

void	do_child(int *tube, char **cmds, char **env)
{
	char	**args;

	args = ft_split(*cmds, ' ');
	if (!do_redirection(args))
	{
		dup2(tube[1], STDOUT_FILENO);
		do_execute(args, env, tube);
	}
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
