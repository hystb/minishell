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

#include "../includes/exec.h"
#include "../includes/minishell.h"


void	add_pids(pid_t value, t_listpids **list)
{
	t_listpids	*new;
	t_listpids	*i;

	new = malloc(sizeof(t_listpids));
	if (!new)
		write_error("Memory allocation error !");
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



void	make_command(t_list	**cmds, char **env)
{
	char	*path;
	int		exec;

	make_redir_inside(*cmds);
	do_builtins(cmds, env);
	if (!(*cmds)->content[0])
		return ;
	path = get_path((char *)(*cmds)->content[0], env);
	if (!path)
		not_found_error((char *)(*cmds)->content[0]);
	exec = execve(path, (char **)(*cmds)->content, env);
	if (exec < 0)
		exit_error();
	free(path);
}

void	do_child(t_list **cmds, char **env, int *fd_in, int tube[2])
{
	if ((*cmds)->previous)
	{
		dup2(*fd_in, STDIN_FILENO);
		close(*fd_in);
	}
	if ((*cmds)->next)
		dup2(tube[1], STDOUT_FILENO);
	close(tube[1]);
	close(tube[0]);
	make_command(cmds, env);
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

void	make_pipe(t_list **cmds, char **env, t_listpids **pids, int *fd_in)
{
	pid_t		pid;
	int			tube[2];

	while (*cmds)
	{
		if (pipe(tube) == -1)
			exit_error();
		pid = fork();
		if (pid == -1)
			exit_error();
		if (pid == 0)
			do_child(cmds, env, fd_in, tube);
		else
		{
			add_pids(pid, pids);
			if ((*cmds)->fd_heredoc)
				close((*cmds)->fd_heredoc);
			do_parent(cmds, fd_in, tube);
		}
	}
	if (*fd_in)
		close(*fd_in);
}
