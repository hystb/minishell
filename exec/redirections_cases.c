/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_cases.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:05:21 by ebillon           #+#    #+#             */
/*   Updated: 2023/02/20 15:19:09 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	do_redirection(t_list *cmds, t_redirect *data)
{
	int	value;

	value = 0;
	value += do_redir_in((char **)cmds->content, data);
	value += do_redir_out((char **)cmds->content, data);
	return (value);
}

int do_redir_in(char **args, t_redirect *data)
{
	if (ft_strncmp(args[0], "<<", 2) == 0)
	{
		do_heredoc(args[1]);
		// wait(NULL);
		return (1);
	}
	else if (ft_strncmp(args[0], "<", 1) == 0)
	{
		// if (do_input(cmds[1]))
			// return (2);
		do_input(args[1], data);
		return (1);
	}
	return (0);
}

int do_redir_out(char **args, t_redirect *data)
{
	if (ft_strncmp(args[0], ">>", 2) == 0)
	{
		do_writing_file(data->tube_out, args[1], 1);
		return (1);
	}
	else if (ft_strncmp(args[0], ">", 1) == 0)
	{
		do_writing_file(data->tube_out, args[1], 0);
		return (1);
	}
	return (0);
}
