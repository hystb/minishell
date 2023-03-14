
#include "../includes/minishell.h"

void	ft_exit(t_data data)
{
	int		val;
	char	**args;

	args = (char **)(*data.cmd_lst)->content;
	val = 0;
	free_data(data);
	if (args_len(args) >= 2)
		val = ft_atoi(args[1]);
	exit(val);
}