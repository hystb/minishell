/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:23:42 by ebillon           #+#    #+#             */
/*   Updated: 2023/01/24 15:17:22 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

/* try to open file and put in on stdin */
void	do_input(char *path, int *tube)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		// la passer a la cmd suivante.
		exit_error();
	}
	close(tube[0]);
	dup2(fd, tube[1]);
	close(fd);
	close(tube[1]);
}

/* open the heredoc */
void	read_here_doc(char *limiter, int *tube)
{
	char	*str;

	close(tube[0]);
	while (1)
	{
		str = readline("heredoc> ");
		if (ft_strncmp(str, limiter, ft_strlen(str)) == 0)
		{
			close(tube[1]);
			exit(0);
		}
		write(tube[1], str, ft_strlen(str));
		write(tube[1], "\n", 1);
		free(str);
	}
}

/* open and use heredoc as stdin with LIMITER as limit */
void	do_heredoc(char *limiter, int *oldtube)
{
	int		tube[2];
	pid_t	pid;

	close(oldtube[1]);
	close(oldtube[0]);
	if (pipe(tube) == -1)
		exit_error();
	pid = fork();
	if (pid == -1)
		exit_error();
	if (pid == 0)
		read_here_doc(limiter, tube);
	else
	{
		wait(NULL);
		close(tube[1]);
		dup2(tube[0], STDIN_FILENO);
		close(tube[0]);
	}	
}
