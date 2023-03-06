/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:31:44 by nmilan            #+#    #+#             */
/*   Updated: 2023/02/20 13:33:35 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

int	is_option(char *arg, int *c)
{
	int	i;

	i = 0;
	if (arg[i] != '-')
		return (0);
	i++;
	if (!arg[i])
	{
		*c++;
		return (0);
	}
	while (arg[i] == 'n')
		i++;
	if (!arg[i] || arg[i] == ' ')
		return (1);
	return (0);
}

void	echo(char **args)
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
		printf("%s", args[i++]);
		if (args[i])
			printf(" ");
	}
	if (!new_line)
		printf("\n");
}