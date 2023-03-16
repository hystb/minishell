/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethaaalpha <ethaaalpha@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:39:23 by ebillon           #+#    #+#             */
/*   Updated: 2023/03/16 15:31:00 by ethaaalpha       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_exit(t_data data)
{
	int		val;
	char	**args;

	args = (char **)(*data.cmd_lst)->content;
	val = 0;
	free_data(data);
	if (args_len(args) >= 2)
		val = ft_atoi(args[1]);
	exit(val);
}
