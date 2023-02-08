#include "../../includes/exec.h"

int	do_redirection(char **cmds, t_redirect *data)
{
	int	value;

	value = 0;
	value += do_redir_in(cmds, data);
	value += do_redir_out(cmds, data);
	return (value);
}

int do_redir_in(char **cmds, t_redirect *data)
{
	if (ft_strncmp(cmds[0], "<<", 2) == 0)
	{
		do_heredoc(cmds[1]);
		// wait(NULL);
		return (1);
	}
	else if (ft_strncmp(cmds[0], "<", 1) == 0)
	{
		// if (do_input(cmds[1]))
			// return (2);
		do_input(cmds[1], data);
		return (1);
	}
	return (0);
}

int do_redir_out(char **cmds, t_redirect *data)
{
	if (ft_strncmp(cmds[0], ">>", 2) == 0)
	{
		do_writing_file(data->tube_out, cmds[1], 1);
		return (1);
	}
	else if (ft_strncmp(cmds[0], ">", 1) == 0)
	{
		do_writing_file(data->tube_out, cmds[1], 0);
		return (1);
	}
	return (0);
}

void check_redir_exec(char **cmds, t_redirect *data)
{
	
}