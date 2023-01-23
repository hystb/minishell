/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 12:50:53 by nmilan            #+#    #+#             */
/*   Updated: 2023/01/23 14:22:13 by nmilan           ###   ########.fr       */
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
		while (map_cmd[i][0][0] == '|')
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
