/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _cases.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:05:21 by ebillon           #+#    #+#             */
/*   Updated: 2023/03/21 13:11:49 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	aux_inside_out(char **args, int mode, int i, t_data data)
{
	int		fd_temp;
	char	*target;

	if (mode)
	{
		target = rechange_target(args[i + 1]);
		if (args[i][2])
			target = rechange_target(args[i] + 2);
		fd_temp = do_writing_file(target, 1, data);
	}
	else
	{
		target = rechange_target(args[i + 1]);
		if (args[i][1])
			target = rechange_target(args[i] + 1);
		fd_temp = do_writing_file(target, 0, data);
	}
	if (dup2(fd_temp, STDOUT_FILENO) == -1)
		perror("");
	close(fd_temp);
	clean_up_redir(args, i);
}

int	aux_inside_in(char **args, int i)
{
	char	*target;

	target = rechange_target(args[i + 1]);
	if (args[i][1])
		target = rechange_target(args[i] + 1);
	if (do_input(target))
		return (1);
	clean_up_redir(args, i);
	return (0);
}

int	make_redir_inside(t_list *cmd, t_data data, int i)
{
	char	**args;

	args = (char **)cmd->content;
	if (cmd->fd_heredoc)
	{
		if (dup2(cmd->fd_heredoc, STDIN_FILENO) == -1)
			perror("");
		close(cmd->fd_heredoc);
	}
	while (args[i])
	{
		if (ft_strncmp(args[i], "<", 1) == 0)
		{
			if (aux_inside_in(args, i))
				return (1);
		}
		else if (ft_strncmp(args[i], ">>", 2) == 0)
			aux_inside_out(args, 1, i, data);
		else if (ft_strncmp(args[i], ">", 1) == 0)
			aux_inside_out(args, 0, i, data);
		else
			i++;
	}
	return (0);
}

void	make_redir_inside_aux(t_list *cmd, int *fd_target, t_data data)
{
	char	**args;
	char	*target;
	int		i;

	if (!cmd)
		return ;
	i = 0;
	args = (char **)cmd->content;
	while (args[i])
	{
		if (*fd_target == 130)
			return ;
		if (ft_strncmp(args[i], "<<", 2) == 0)
		{
			if (*fd_target)
				close(*fd_target);
			target = rechange_target(args[i + 1]);
			if (args[i][2])
				target = rechange_target(args[i] + 2);
			*fd_target = do_heredoc(target, data);
			clean_up_redir(args, i);
		}
		else
			i++;
	}
}
