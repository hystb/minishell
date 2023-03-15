/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:49:52 by ebillon           #+#    #+#             */
/*   Updated: 2023/03/07 14:28:10 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_pids(pid_t value, t_listpids **list, t_data data)
{
	t_listpids	*new;
	t_listpids	*i;

	new = malloc(sizeof(t_listpids));
	if (!new)
		write_error("Memory allocation error !", data);
	new->pid = value;
	new->next = NULL;
	i = *list;
	if (i)
	{
		while (i->next)
			i = i->next;
		i->next = new;
	}
	else
		*list = new;
}

void	make_command(t_list	**cmds, char **env, t_data data)
{
	char	*path;
	int		exec;

	make_redir_inside(*cmds, data);
	if (!(*cmds)->content[0] || is_builtins(cmds))
		return ;
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
	char **env;

	if ((*cmds)->previous)
	{
		dup2(*fd_in, STDIN_FILENO);
		close(*fd_in);
	}
	if ((*cmds)->next)
		dup2(tube[1], STDOUT_FILENO);
	close(tube[1]);
	close(tube[0]);
	env = get_env_from_lst(data);
	if (!env)
		write_error("Memory allocation error !", data);
	make_command(cmds, env, data);
	free_tab(env);
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
			if (do_builtins(data) < 0)
				add_pids(pid, pids, data);
			if ((*cmds)->fd_heredoc)
				close((*cmds)->fd_heredoc);
			do_parent(cmds, fd_in, tube);
		}
	}
	if (*fd_in)
		close(*fd_in);
}
