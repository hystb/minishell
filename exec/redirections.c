/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 11:23:42 by ebillon           #+#    #+#             */
/*   Updated: 2023/03/07 14:27:41 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
#include "../includes/minishell.h"

/* try to open file and put in on stdin */
int	do_input(char *path)
{
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		perror("");
		return (1);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

/* write in a file depending on the file mode opening */
int	do_writing_file(char *path, int mode)
{
	int		fd_out;

	if (mode == 1)
		fd_out = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		fd_out = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_out == -1)
		exit_error();
	return (fd_out);
}

void	check_free(char *a, char *b)
{
	if (a)
		free(a);
	if (b)
		free(b);
}

/* open and use heredoc as stdin with LIMITER as limit */
void	do_heredoc(char *limiter)
{
	char	*str;
	int		fd;

	limiter = ft_strjoin(ft_strdup(limiter), ft_strdup("\n"));
	fd = open(HEREDOC_FILE, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd == -1)
		write_error("Heredoc file error.");
	g_signal_handle = fd;
	while (1)
	{
		write(STDIN_FILENO, "> ", 2);
		str = get_next_line(STDIN_FILENO);
		if (ft_strncmp(str, limiter, ft_strlen(str)) == 0)
			break ;
		write(fd, str, ft_strlen(str));
		free(str);
	}
	check_free(str, limiter);
	close(fd);
	fd = open(HEREDOC_FILE, O_RDONLY);
	dup2(fd, STDIN_FILENO);
	close(fd);
	unlink(HEREDOC_FILE);
}
