#include "../includes/exec.h"
#include "../includes/builtins.h"

void	do_builtins(t_list	**cmds, char **env)
{
	char	*arg;

	arg = (char *)(*cmds)->content[0];
	if (!ft_strncmp(arg, "echo", ft_strlen(arg)))
		echo((char **)(*cmds)->content);
	else if (!ft_strncmp(arg, "pwd", ft_strlen(arg)))
		pwd();
	(void) env;
}
