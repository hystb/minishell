
#include "../includes/minishell.h"

int		get_env_lenght(t_data data)
{
	int		lenght;
	t_env	*env;

	lenght = 0;
	env = *data.env_var;
	while (env)
	{
		env = env->next;
		lenght++;
	}
	return (lenght);
}

char	*get_item_env(t_data data, char *key)
{
	t_env	*env;

	env = *data.env_var;
	while (env)
	{
		if (ft_strnstr(env->name_var, key, (ft_strlen(key) + 1)))
		{
			return (env->content_var);
		}
		env = env->next;
	}
	return (NULL);
}

void	add_value_env(char *key, char *value, t_data data)
{
	t_env	*item;

	item = malloc(sizeof(*item));
	if (!item)
		write_error("Memory allocation error !", data);
	item->previous = NULL;
	item->next = NULL;
	item->content_var = value;
	item->name_var = ft_strdup(key);
	env_add_back(data.env_var, item);
}

void	set_value_env(char *key, char *value, t_data var_lst)
{
	t_env	*env;

	if (!value)
		write_error("Memory allocation error !", var_lst);
	env = *var_lst.env_var;
	while (env)
	{
		if (ft_strnstr(env->name_var, key, (ft_strlen(key) + 1)))
		{
			free(env->content_var);
			env->content_var = value;
			return ;
		}
		env = env->next;
	}
	add_value_env(key, value, var_lst);
}

void delete_item_env(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strncmp(env->name_var, key, ft_strlen(env->name_var)))
		{
			env->previous->next = env->next;
			env->next->previous = env->previous;
			free(env->content_var);
			free(env->name_var);
			free(env);
			break ;
		}
		env = env->next;
	}
}