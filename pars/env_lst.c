#include "../includes/minishell.h"

t_env	*envnew(char *content, int end)
{
	t_env	*new;

	new = malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->name_var = ft_substr(content, 0, end);
	new->content_var = ft_substr(content, end + 1, ft_strlen(&content[end]));
	new->next = NULL;
	new->previous = NULL;
	return (new);
}

void	env_add_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	tmp = *lst;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->previous = tmp;
}

void	free_env_var(t_env **env)
{
	t_env	*tmp;
	t_env	*lst;

	/*if (!*env)
	{
		if (env)
			free(env);
		return ;
	}*/
	lst = *env;
	while (lst)
	{
		tmp = lst->next;
		free(lst->name_var);
		free(lst->content_var);
		free(lst);
		lst = tmp;
	}
	free(env);
}
