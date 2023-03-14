
#include "../includes/minishell.h"
#include "../includes/builtins.h"
#include "../includes/exec.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

char	**cp_var_name(t_data data)
{
	t_env	*env;
	char	**tab;
	int		i;

	env = *data.env_var;
	tab = malloc((get_env_lenght(data) + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (env)
	{
		tab[i] = ft_strdup(env->name_var);
		if (!tab[i])
			return (NULL);
		i++;
		env = env->next;
	}
	tab[i] = NULL;
	return (tab);
}

void	sort_tab(char **tab)
{
	int		i;
	int		sorted;
	char	*tmp;

	i = 0;
	sorted = 1;
	while (sorted)
	{
		while (tab[i])
		{
			if (tab[i + 1] && ft_strncmp(tab[i], tab[i + 1], ft_strlen(tab[i])) > 0)
			{	
				sorted = 1;
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				break ;
			}
			i++;
			sorted = 0;
		}
		i = 0;
	}
}

int	do_export_nargs(t_data data)
{
	char	**args;
	int		i;

	args = cp_var_name(data);
	if (!args)
	{
		free_tab(args);
		write_error("Memory Allocation error !");
	}
	sort_tab(args);
	i = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], "?", ft_strlen(args[i])))
			printf("declare -x %s=%s\n", args[i], get_item_env(data, args[i]));
		i++;
	}
	free_tab(args);	
	return (0);
}