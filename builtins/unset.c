#include "../includes/minishell.h"

int check_unset_str(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if ((!ft_isalnum(str[i])) && str[i] != '_')
		{
			write(STDERR_FILENO, "minishell: unset: `", 20);
			write(STDERR_FILENO, &str[i], 1);
			write(STDERR_FILENO, "': not a valid identifier\n", 27);
			return (1);
		}
		i++;
	}
	return (0);
}

int	unset(t_data data, char **vars)
{
	int		i;
	int		val;
	t_env	*env;

	val = 0;
	env = *data.env_var;
	i = 1;
	while (vars[i])
	{
		if (check_unset_str(vars[i]))
			val++;
		else
			delete_item_env(env, vars[i]);
		i++;
	}
	if (val)
		return (1);
	return (0);
}