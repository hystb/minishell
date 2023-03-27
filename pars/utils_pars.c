/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 16:29:22 by nmilan            #+#    #+#             */
/*   Updated: 2023/03/27 16:02:26 by nmilan           ###   ########.fr       */
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

void	replace_pipe_in_quote(char ***map)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (map && map[i])
	{
		j = 0;
		while (map[i][j])
		{
			k = 0;
			while (map[i][j][k])
			{
				if (map[i][j][k] == 28)
					map[i][j][k] = '|';
				k++;
			}
			j++;
		}
		i++;
	}
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

void	print_undefine(char *s1, char *s2, char *s3, char c)
{
	ft_putstr_fd(s1, 2);
	if (s2)
		ft_putstr_fd(s2, 2);
	else if (c)
		ft_putchar_fd(c, 2);
	ft_putstr_fd(s3, 2);
	return ;
}
