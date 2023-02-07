/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:49:52 by ebillon           #+#    #+#             */
/*   Updated: 2023/01/30 15:23:03 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

/* check about parent activity and redirections possibilites */
void	pre_redirect(char **cmds, int argc, char **env, t_redirect *data)
{
	int	value;

	value = do_redirection(ft_split(*cmds, ' '), data);
	printf("je pre_redirect avec %s | %d\n", cmds[0], data->tube_out);
	if (value)
	{
		argc -= value;
		if (argc >= 1)
			pre_redirect(cmds + value, argc, env, data);
		close(data->tube_out);
	}
	else
	{
		if (data->tube_out >= 0)
			dup2(data->tube_out, STDIN_FILENO);
		else
		{
			dup2(0, STDIN_FILENO);
		}
			// close(STDIN_FILENO);
		redirect(cmds, argc, env, data);
		close(data->tube_out);
	}
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
			data->tube_out = tube[0];
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

int	do_redirection(char **cmds, t_redirect *data)
{
	if (ft_strncmp(cmds[0], "<<", 2) == 0)
	{
		do_heredoc(cmds[1]);
		return (1);
	}
	else if (ft_strncmp(cmds[0], "<", 1) == 0)
	{
		// if (do_input(cmds[1]))
			// return (2);
		do_input(cmds[1], data);
		return (1);
	}
	else if (ft_strncmp(cmds[0], ">>", 2) == 0)
	{
		do_writing_file(data->tube_out, cmds[1], 1);
		return (1);
	}
	else if (ft_strncmp(cmds[0], ">", 1) == 0)
	{
		do_writing_file(data->tube_out, cmds[1], 0);
		return (1);
	}
	return (0);
}

// go and make the redirection ( mettre en place les buildints ici aussi) passer a la commande suivante si echec
/* change here by passing the cmd */
void	do_child(int *tube, char **cmds, char **env)
{
	char	**args;

	args = ft_split(*cmds, ' ');
	dup2(tube[1], STDOUT_FILENO);
	do_execute(args, env, tube);
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
	int	i;
	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}
