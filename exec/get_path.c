/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:46:49 by ebillon           #+#    #+#             */
/*   Updated: 2023/02/20 13:05:16 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

/* free split data */
void	free_split(char **tab, int exit)
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
		write_error("Memory allocation error !  wadwadwadawdwadwadwadaaa");
}

/* free s2 before join */
char	*ft_str_fjoin(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s2);
	return (res);
}

/* get the path of the command, return null if not found */
char	*get_path(char *cmd, char **env)
{
	int		i;
	char	**splited;
	char	*joined;

	i = 0;
	if (access(cmd, O_RDONLY) == 0)
		return (ft_strdup(cmd));
	while (ft_strncmp("PATH=", *env, 5))
		env++;
	splited = ft_split((*env) + 5, ':');
	if (splited[i] == NULL)
		free_split(splited, 1);
	while (splited[i])
	{
		joined = ft_str_fjoin(splited[i], ft_strjoin("/", cmd));
		if (!joined)
			free_split(splited, 1);
		if (access(joined, O_RDONLY) == 0)
		{
			free_split(splited, 0);
			return (joined);
		}
		free(joined);
		i++;
	}
	free_split(splited, 0);
	return (NULL);
}
