/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:49:52 by ebillon           #+#    #+#             */
/*   Updated: 2023/03/21 14:55:54 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	make_command(t_list	**cmds, char **env, t_data data)
{
	char	*path;
	int		val;
	int		exec;

	if (make_redir_inside(*cmds, data))
		exit_error(data);
	if (!(*cmds)->content[0])
		return ;
	if (is_builtins(cmds))
	{
		val = do_builtins(data);
		free_data(data);
		exit (val);
	}
	path = get_path((char *)(*cmds)->content[0], env, data);
	if (!path)
		not_found_error((char *)(*cmds)->content[0], data);
	exec = execve(path, (char **)(*cmds)->content, env);
	free(path);
	if (exec < 0)
		exit_error(data);
}

void	do_child(t_list **cmds, t_data data, int *fd_in, int tube[2])
{
	char	**env;

	if ((*cmds)->previous)
	{
		if (dup2(*fd_in, STDIN_FILENO) == -1)
			perror("");
		close(*fd_in);
	}
	if ((*cmds)->next)
	{
		if (dup2(tube[1], STDOUT_FILENO) == -1)
			perror("");
	}
	close(tube[1]);
	close(tube[0]);
	env = get_env_from_lst(data);
	if (!env)
		write_error("Memory allocation error !", data);
	make_command(cmds, env, data);
	free_tab(env);
	free_data(data);
	exit(EXIT_SUCCESS);
}

void	do_parent(t_list **cmds, int *fd_in, int tube[2])
{
	if ((*cmds)->previous)
		close(*fd_in);
	if ((*cmds)->next)
		*fd_in = tube[0];
	else
		close(tube[0]);
	close(tube[1]);
	(*cmds) = (*cmds)->next;
	while (*cmds && ft_strncmp((char *)(*cmds)->content[0], "|", 1) == 0)
		(*cmds) = (*cmds)->next;
}

int	make_only(t_data data, t_listpids **pids, int *fd_in)
{
	t_list	**cmds;
	int		val;
	int		old_out;
	int		old_in;

	cmds = data.cmd_lst;
	if (is_builtins(cmds))
	{
		old_out = dup(STDOUT_FILENO);
		old_in = dup(STDIN_FILENO);
		if (old_in < 0 || old_in < 0)
			return (quit_simple(data, 1));
		if (make_redir_inside(*cmds, data))
			return (quit_redir(old_out, old_in));
		val = do_builtins(data);
		if (dup2(old_out, STDOUT_FILENO) == -1 || \
		dup2(old_in, STDIN_FILENO) == -1)
			return (quit_simple(data, 1));
		close(old_in);
		close(old_out);
		set_value_env("?", ft_itoa(val), data);
	}
	else
		make_pipe(data, pids, fd_in);
	return (0);
}

void	make_pipe(t_data data, t_listpids **pids, int *fd_in)
{
	pid_t		pid;
	t_list		**cmds;
	int			tube[2];

	cmds = data.cmd_lst;
	while (*cmds)
	{
		if (pipe(tube) == -1)
			exit_error(data);
		pid = fork();
		if (pid == -1)
			exit_error(data);
		if (pid == 0)
			do_child(cmds, data, fd_in, tube);
		else
		{
			add_pids(pid, pids, data);
			if ((*cmds)->fd_heredoc)
				close((*cmds)->fd_heredoc);
			do_parent(cmds, fd_in, tube);
		}
	}
	if (*fd_in)
		close(*fd_in);
}
