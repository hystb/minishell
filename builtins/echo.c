/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:31:44 by nmilan            #+#    #+#             */
/*   Updated: 2023/03/31 12:55:48 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_option(char *arg, int *c)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (0);
	i++;
	if (!arg[i])
	{
		*c = *c + 1;
		return (0);
	}
	while (arg[i] == 'n')
		i++;
	if (!arg[i] || arg[i] == ' ')
		return (1);
	return (0);
}

int	echo(char **args)
{
	int	i;
	int	res;
	int	new_line;

	new_line = 0;
	i = 1;
	while (args[i])
	{
		res = is_option(args[i], &i);
		if (!res)
			break ;
		i++;
		new_line++;
	}
	while (args[i])
	{
		write(STDOUT_FILENO, args[i], ft_strlen(args[i]));
		i++;
		if (args[i])
			write(STDOUT_FILENO, " ", 1);
	}
	if (!new_line)
		write(STDOUT_FILENO, "\n", 1);
	return (EXIT_SUCCESS);
}
