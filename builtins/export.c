#include "../includes/builtins.h"
#include "../includes/minishell.h"

int	ft_export(char	*data, t_data var)
{
	int	i;

	i = 0;
	while (data[i] && data[i] != '=')
	{
		i++;
	}
	env_add_back(var.env_var, envnew(data, i));
}