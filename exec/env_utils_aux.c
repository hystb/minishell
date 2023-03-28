/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_aux.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:39:23 by ebillon           #+#    #+#             */
/*   Updated: 2023/03/28 16:23:53 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_env_from_lst(t_data data, int i)
{
	char	**res;
	t_env	*env;

	env = *data.env_var;
	res = malloc((sizeof(char *)) * (get_env_lenght(data) + 1));
	if (!res)
		return (NULL);
	while (env)
	{
		if (ft_strncmp(env->name_var, "?", ft_strlen(env->name_var)))
		{
			res[i] = ft_strjoin(ft_strdup(env->name_var), \
			ft_strjoin(ft_strdup("="), ft_strdup(env->content_var)));
			if (!res[i])
			{
				res[i] = NULL;
				free_tab(res);
				return (NULL);
			}
			i++;
		}	
		env = env->next;
	}
	res[i] = NULL;
	return (res);
}
