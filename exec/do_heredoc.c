
#include "../includes/exec.h"
#include "../includes/minishell.h"

void	check_free(char *a, char *b)
{
	if (a)
		free(a);
	if (b)
		free(b);
}

void	do_heredoc_child(char *str, char *limiter, int fd[2])
{
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
		write(fd[1], str, ft_strlen(str));
		free(str);
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

int	do_heredoc(char *limiter)
{
	char	*str;
	int		pid;
	int		fd[2];

	limiter = ft_strjoin(ft_strdup(limiter), ft_strdup("\n"));
	if (pipe(fd) == -1)
		exit_error();
	pid = fork();
	if (pid == -1)
		exit_error();
	if (pid == 0)
		do_heredoc_child(str, limiter, fd);
	else
		return (do_heredoc_parent(limiter, fd, pid));
	return (-1);
}