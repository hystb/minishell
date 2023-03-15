
#include "../includes/minishell.h"

int	go_to(t_data data, char *dest)
{
	char	*path_old;

	path_old = get_item_env(data, "PWD");
	if (chdir(dest) == -1)
	{
		perror("");
		return (1);
	}
	set_value_env("OLDPWD", ft_strdup(path_old), data);
	return (0);
}

int	args_len(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	cd(t_data data, t_list *cmds)
{
	char	**args;
	char	*path;

	args = (char **)cmds->content;
	if (args_len(args) == 1)
		path = get_item_env(data, "HOME");
	else if (!ft_strncmp(args[1], "-", ft_strlen(args[1])))
		path = get_item_env(data, "OLDPWD");
	else
		path = args[1];
	return (go_to(data, path));
}