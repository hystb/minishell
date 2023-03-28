/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:39:23 by ebillon           #+#    #+#             */
/*   Updated: 2023/03/28 16:17:41 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_syntaxe(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	while (arg[i])
	{
		if (arg[i] < '0' || arg[i] > '9')
		{
			write(2, "minishell: exit: ", 18);
			write(2, arg, ft_strlen(arg));
			write(2, ": numeric argument required\n", 29);
			return (2);
		}
		i++;
	}
	return (ft_atoi(arg));
}

void	ft_exit(t_data data)
{
	int		val;
	char	**args;

	args = (char **)(*data.cmd_lst)->content;
	val = ft_atoi(get_item_env(data, "?"));
	if (args_len(args) == 2)
		val = check_syntaxe(args[1]);
	if (args_len(args) > 2)
	{
		val = 1;
		write(2, "minishell: exit: too many arguments\n", 37);
	}
	write(1, "exit\n", 5);
	rl_clear_history();
	free_data(data);
	exit(val);
}
