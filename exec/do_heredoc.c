/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethaaalpha <ethaaalpha@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:39:23 by ebillon           #+#    #+#             */
/*   Updated: 2023/03/16 15:32:00 by ethaaalpha       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_free(char *a, char *b)
{
	if (a)
		free(a);
	if (b)
		free(b);
}

void	heredoc_loop(char *str, t_data data, int fd[2])
{
	char	*tmp;

	tmp = check_var(str, data, 0, -1);
	while (ft_strncmp(tmp, str, ft_strlen(tmp)))
	{
			str = tmp;
			tmp = check_var(str, data, 0, -1);
	}
	str = tmp;
	write(fd[1], str, ft_strlen(str));
	if (str[ft_strlen(str) - 1] != '\n')
		write(fd[1], "\n", 1);
	free(str);
}

void	do_heredoc_child(char *limiter, int fd[2], t_data data)
{
	char	*str;

	close(fd[0]);
	g_signal_handle = fd[1];
	while (1)
	{
		write(STDIN_FILENO, "> ", 2);
		str = get_next_line(STDIN_FILENO);
		if (!str)
			break ;
		if (ft_strncmp(str, limiter, ft_strlen(str)) == 0)
			break ;
		heredoc_loop(str, data, fd);
	}
	check_free(str, limiter);
	close(fd[1]);
	exit(EXIT_SUCCESS);
}

int	do_heredoc_parent(char *limiter, int fd[2], int pid)
{
	int		status;

	waitpid(pid, &status, 0);
	if (limiter)
		free(limiter);
	close(fd[1]);
	if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
	{
		close(fd[0]);
		return (-130);
	}
	return (fd[0]);
}

int	do_heredoc(char *limiter, t_data data)
{
	int		pid;
	int		fd[2];

	limiter = ft_strjoin(ft_strdup(limiter), ft_strdup("\n"));
	if (pipe(fd) == -1)
		exit_error(data);
	pid = fork();
	if (pid == -1)
		exit_error(data);
	if (pid == 0)
		do_heredoc_child(limiter, fd, data);
	else
		return (do_heredoc_parent(limiter, fd, pid));
	return (-1);
}
