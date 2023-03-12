#include "../includes/builtins.h"
#include "../includes/minishell.h"
#include "../includes/exec.h"

int	unset(t_data data, char **vars)
{
	int		i;
	t_env	*env;

	env = *data.env_var;
	i = 1;
	while (vars[i])
	{
		delete_item_env(env, vars[i]);
		i++;
	}
	return (0);
}