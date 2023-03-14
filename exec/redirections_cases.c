/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_cases.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:05:21 by ebillon           #+#    #+#             */
/*   Updated: 2023/03/07 14:09:05 by ebillon          ###   ########.fr       */
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

void	aux_inside_in(char **args, int i)
{
	if (do_input(args[i + 1]))
		exit(EXIT_FAILURE); //handle leaks here
	clean_up_redir(args, i);
}

void	make_redir_inside(t_list *cmd)
{
	char	**args;
	int		i;

	i = 0;
	args = (char **)cmd->content;
	if (cmd->fd_heredoc)
	{
		dup2(cmd->fd_heredoc, STDIN_FILENO);
		close(cmd->fd_heredoc);
	}
	while (args[i])
	{
		if (ft_strncmp(args[i], "<", 1) == 0)
			aux_inside_in(args, i);
		else if (ft_strncmp(args[i], ">>", 2) == 0)
			aux_inside_out(args, 1, i);
		else if (ft_strncmp(args[i], ">", 1) == 0)
			aux_inside_out(args, 0, i);
		else
			i++;
	}
}

void	put_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		puts(tab[i]);
		i++;
	}
}

void	make_redir_inside_aux(t_list *cmd, int *fd_target, t_data data)
{
	char	**args;
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
			*fd_target = do_heredoc(args[i + 1], data);
			clean_up_redir(args, i);
		}
		else
			i++;
	}
}
