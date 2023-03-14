#include "../includes/minishell.h"

char **get_env_from_lst(t_data data)
{
	char 	**res;
	int		i;
	t_env	*env;

	env = *data.env_var;
	res = malloc((sizeof(char *)) * (get_env_lenght(data) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (env)
	{
		res[i] = ft_strjoin(ft_strdup(env->name_var), ft_strjoin(ft_strdup("="), ft_strdup(env->content_var)));
		if (!res[i])
		{
			res[i] = NULL;
			free_tab(res);
			return (NULL);
		}
		env = env->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}