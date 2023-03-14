
#include "../includes/exec.h"
#include "../includes/minishell.h"

void	check_free(char *a, char *b)
{
	if (a)
		free(a);
	if (b)
		free(b);
}

char	*check_var(char *arg, t_data var_lst, int j)
{
	int		is_sp_quote;
	int		i;
	char	*var;

	var = arg;
	is_sp_quote = 0;
	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '\'' && is_sp_quote == 0)
			is_sp_quote = 1;
		else if (arg[i] == '\'' && is_sp_quote == 1)
			is_sp_quote = 0;
		if (arg[i] == '$' && is_sp_quote == 0)
		{
			j = i + 1;
			while (arg[i] != ' ' && arg[i] != '\f' && arg[i] != '\n'
				&& arg[i] != '\t' && arg[i] != '\v' && arg[i] != '\r'
				&& arg[i] && arg[i] != '"')
				i++;
			var = ft_substr(arg, j, i - j);
			var = sub_env_var(var, arg, j - 1, var_lst);
			return (var);
		}
	}
	return (var);
}

void	do_heredoc_child(char *limiter, int fd[2], t_data data)
{
	char	*str;
	char	*tmp;

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
		tmp = check_var(str, data, 0);
		while (ft_strncmp(tmp, str, ft_strlen(tmp)))
		{
			str = tmp;
			tmp = check_var(str, data, 0);
		}
		str = tmp;
		write(fd[1], str, ft_strlen(str));
		if (str[ft_strlen(str)] != '\n')
			write(fd[1], "\n", 1);
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

int	do_heredoc(char *limiter, t_data data)
{
	int		pid;
	int		fd[2];

	limiter = ft_strjoin(ft_strdup(limiter), ft_strdup("\n"));
	if (pipe(fd) == -1)
		exit_error();
	pid = fork();
	if (pid == -1)
		exit_error();
	if (pid == 0)
		do_heredoc_child(limiter, fd, data);
	else
		return (do_heredoc_parent(limiter, fd, pid));
	return (-1);
}