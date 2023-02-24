/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:29:22 by nmilan            #+#    #+#             */
/*   Updated: 2023/01/25 17:23:07 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_tablen(char ***map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;

	if (!map)
		return (0);
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			j++;
			count++;
		}
		i++;
	}
	return (count - 1);
}

void	jump_next_pipe(int *last_pipe, int *last_splited, char **splited)
{
	if (!splited[*last_splited])
		return ;
	if (have_sign(splited[*last_splited + 1]))
	{
		//free(splited[*last_splited]);
		*last_splited = *last_splited + 1;
	}
	*last_pipe = 0;
}

int	have_sign(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>')
			return (1);
		i++;
	}
	return (0);
}
