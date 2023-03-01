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

void	print_args(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (arg[0] == '\'' || arg[0] == '\"')
	{
		arg[len - 1] = '\0';
		printf("%s", arg + 1);
	}
	else
		printf("%s", arg);
}

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

void	echo(char	**args)
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
		print_args(args[i++]);
		if (args[i])
			printf(" ");
	}
	if (!new_line)
		printf("\n");
}