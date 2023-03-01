/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:49:52 by ebillon           #+#    #+#             */
/*   Updated: 2023/02/22 13:41:23 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"


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

void	clean_up_redir(char **args, int i)
{
	int		org;
	char	*save;

	org = i;
	save = args[i];
	while (args[i])
	{
		args[i] = args[i + 1];
		i++;
	}
	i = org;
	free(save);
	save = args[i];
	while (args[i])
	{
		args[i] = args[i + 1];
		i++;
	}
	free(save);
}

void put_tab(char **tab)
{
	int	i;

	i = 0;
	while(tab[i])
	{
		fprintf(stderr,"%s ", tab[i]);
		i++;
	}
	fprintf(stderr,"\n");
}

void	aux_inside_out(char **args, int mode, int i)
{
	int	fd_temp;

	if (mode)
		fd_temp = do_writing_file(args[i + 1], 1);
	else
		fd_temp = do_writing_file(args[i + 1], 0);
	dup2(fd_temp, STDOUT_FILENO);
	close(fd_temp);
	clean_up_redir(args, i);
}

void	aux_inside_in(char **args, int mode, int i)
{
	if (mode)
		do_heredoc(args[i + 1]);
	else
	{
		if (do_input(args[i + 1]))
			exit(EXIT_FAILURE); //handle leaks here
	}
	clean_up_redir(args, i);
}

void	make_redir_inside(t_list *cmd, char **env)
{
	char	**args;
	int		i;

	i = 0;
	args = (char **)cmd->content;
	while (args[i])
	{
		if (ft_strncmp(args[i], "<<", 2) == 0)
			aux_inside_in(args, 1, i);
		else if (ft_strncmp(args[i], "<", 1) == 0)
			aux_inside_in(args, 0, i);
		else if (ft_strncmp(args[i], ">>", 2) == 0)
			aux_inside_out(args, 1, i);
		else if (ft_strncmp(args[i], ">", 1) == 0)
			aux_inside_out(args, 0, i);
		else
			i++;
	}
}

void	make_command(t_list	**cmds, char **env)
{
	char	*path;
	int		exec;
	
	make_redir_inside(*cmds, env);
	if (!(*cmds)->content[0]) //meaning that there were just a redir
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
	if ((*cmds)->previous) //only if not first command
	{
		dup2(*fd_in, STDIN_FILENO);
		close(*fd_in);
	}
	if ((*cmds)->next) //only if not last command
		dup2(tube[1], STDOUT_FILENO);
	close(tube[1]);
	close(tube[0]);
	make_command(cmds, env); //execute command function with execve
	exit(EXIT_SUCCESS);
}

void	do_parent(t_list **cmds, char **env, int *fd_in, int tube[2])
{
	if ((*cmds)->previous)
		close(*fd_in);
	if ((*cmds)->next)
		*fd_in = tube[0];
	close(tube[1]);
	(*cmds) = (*cmds)->next;
	while (*cmds && ft_strncmp((char *)(*cmds)->content[0], "|", 1) == 0)
		(*cmds) = (*cmds)->next;
}

void	make_pipe(t_list **cmds, char **env, t_listpids **pids, int *fd_in)
{
	pid_t		pid;
	int 		tube[2];

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
			add_pids(pid, pids); //add pid to chained list of pids (used to waitpid them after)
			do_parent(cmds, env, fd_in, tube);
		}
	}
}