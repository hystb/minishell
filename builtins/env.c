
#include "../includes/exec.h"
#include "../includes/minishell.h"

int	env(t_data data)
{
	t_env 	*temp;

	temp = *(data.env_var);
	while (temp)
	{
		printf("%s=%s\n", temp->name_var, temp->content_var);
		temp = temp->next;
	}
	return (0);
}