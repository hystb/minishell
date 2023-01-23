/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 12:46:49 by ebillon           #+#    #+#             */
/*   Updated: 2023/01/20 13:33:17 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

/* do the command */
void	do_execute(char **args, char **env, int *tube)
{
	char	*cmd;

	if (access(cmd, O_RDONLY) == -1)
		cmd = get_path(*args, env);
	else
		cmd = ft_strdup(*args);
	close(tube[0]);
	if (cmd)
	{
		if (execve(cmd, args, env) == -1)
			exit_error();
	}
	else
		not_found_error(*args);
	close(tube[1]);
	free(cmd);
	free(args);
}

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
		exit_error();
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
	return (NULL);
}
