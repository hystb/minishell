/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:46:49 by ebillon           #+#    #+#             */
/*   Updated: 2023/03/27 14:58:52 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* free split data */
void	free_split(char **tab, int exit, t_data data)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	if (exit == 1)
		write_error("Memory allocation error !", data);
}

/* free s2 before join */
char	*ft_str_fjoin(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s2);
	return (res);
}

char	**get_splited_env(char **env, t_data data)
{
	char	**splited;

	while (*env && ft_strncmp("PATH=", *env, 5))
		env++;
	if (!*env)
		return (NULL);
	splited = ft_split((*env) + 5, ':');
	if (splited[0] == NULL)
		free_split(splited, 1, data);
	return (splited);
}

/* get the path of the command, return null if not found */
char	*get_path(char *cmd, char **env, t_data data)
{
	int		i;
	char	**splited;
	char	*joined;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	splited = get_splited_env(env, data);
	while (splited && splited[i])
	{
		joined = ft_strjoin(ft_strdup(splited[i]), ft_strjoin(ft_strdup("/"), \
		ft_strdup(cmd)));
		if (!joined)
			free_split(splited, 1, data);
		if (access(joined, X_OK) == 0)
		{
			free_split(splited, 0, data);
			return (joined);
		}
		free(joined);
		i++;
	}
	if (splited)
		free_split(splited, 0, data);
	return (NULL);
}
