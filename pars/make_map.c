/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:50:53 by nmilan            #+#    #+#             */
/*   Updated: 2023/01/24 16:57:48 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	make_map_pipe(char ***map_cmd, char **splited, int end, int start)
{
	static int	i = 0;
	int			j;
	char		**cmd;
	char		**pipe;

	j = 0;
	cmd = malloc(sizeof(char *) * ((end - start) + 2));
	pipe = malloc(sizeof(char *) * 2);
	if (!cmd || !pipe)
	{
		//put exit funct
		exit(1);
	}
	while (start < end)
	{
		cmd[j++] = splited[start++];
	}
	cmd[j] = NULL;
	pipe[0] = splited[end];
	pipe[1] = NULL;
	map_cmd[i++] = cmd;
	map_cmd[i++] = pipe;
	map_cmd[i] = NULL;
	if (last_pipe(splited, (ft_tablen(map_cmd) + 1)))
		i = 0;
}

int	last_pipe(char **splited, int i)
{
	if (splited[i] && splited[i + 1] && (splited[i + 1][0] == '<'
		|| splited[i + 1][0] == '>'))
		i++;
	while (splited[i])
	{
		if (splited[i][0] == '|')
			return (0);
		i++;
	}
	return (1);
}

void	make_map(char ***map_cmd, char **splited, int end, int start)
{
	int		i;
	int		j;
	char	**cmd;

	j = 0;
	i = 0;
	cmd = malloc(sizeof(char *) * ((end - start) + 2));
	if (!cmd)
	{
		//put exit funct
		exit(1);
	}
	if (start > 0)
	{
		while (map_cmd[i])
			i++;
	}
	while (start <= end)
	{
		cmd[j++] = splited[start++];
	}
	cmd[j] = NULL;
	map_cmd[i++] = cmd;
	map_cmd[i] = NULL;
}

void	change_space(char *str, int end, int start, int type)
{
	int	i;

	i = 0;
	if (type == 1)
	{
		while (start < end)
		{
			if (str[start] == ' ')
			{
				str[start] = 31;
			}
			start++;
		}
	}
	else
	{
		while (str[i])
		{
			if (str[i] == 31)
				str[i] = ' ';
			i++;
		}
	}
}

void	change_split(char **splited)
{
	int	i;

	i = 0;
	while (splited[i])
	{
		change_space(splited[i], 0, 0, 2);
		i++;
	}
}
