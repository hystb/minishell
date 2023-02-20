#include "../../includes/exec.h"

int	do_redirection(char **args, t_redirect *data)
{
	int	value;

	value = 0;
	value += do_redir_in(args, data);
	value += do_redir_out(args, data);
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
