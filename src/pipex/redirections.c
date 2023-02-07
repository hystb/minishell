/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:23:42 by ebillon           #+#    #+#             */
/*   Updated: 2023/01/30 16:21:29 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

/* try to open file and put in on stdin */
int	do_input(char *path, t_redirect *data)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		data->tube_out = -1;
		perror("");
		return (1);
	}
	dup2(fd, data->tube_out);
	// dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

/* write in a file depending on the file mode opening */
void	do_writing_file(int fd_in, char *path, int mode)
{
	char	buff[1];
	int		fd_out;

	if (mode == 1)
		fd_out = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd_out = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_out == -1)
		exit_error();
	printf("le fd_in %d\n", fd_in);
	if (fd_in >= 0)
	{
		while (read(fd_in, buff, 1))
			write(fd_out, buff, 1);
	}
	close(fd_out);
}

/* open the heredoc */
void	read_here_doc(char *limiter, int *tube)
{
	char	*str;
	int		fd;

	close(tube[0]);
	while (1)
	{
		str = readline("heredoc> ");
		if (ft_strncmp(str, limiter, ft_strlen(limiter)) == 0)
		{
			free(str);
			close(tube[1]);
			exit(0);
		}
		write(tube[1], str, ft_strlen(str));
		write(tube[1], "\n", 1);
		free(str);
	}
}

/* open and use heredoc as stdin with LIMITER as limit */
void	do_heredoc(char *limiter)
{
	int		tube[2];
	pid_t	pid;
	
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
		// char *buff;
		// while (read(tube[0], buff, 1))
			// write(1, buff, 1);
		dup2(tube[0], STDIN_FILENO);
		close(tube[0]);
	}	
}
