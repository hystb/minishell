/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:39:23 by ebillon           #+#    #+#             */
/*   Updated: 2023/03/29 13:09:18 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtins(t_list	**cmds)
{
	char	*arg;

	arg = (char *)(*cmds)->content[0];
	if (!arg)
		return (0);
	if (!ft_strcmp(arg, "echo"))
		return (1);
	else if (!ft_strcmp(arg, "cd"))
		return (1);
	else if (!ft_strcmp(arg, "pwd"))
		return (1);
	else if (!ft_strcmp(arg, "export"))
		return (1);
	else if (!ft_strcmp(arg, "unset"))
		return (1);
	else if (!ft_strcmp(arg, "env"))
		return (1);
	else if (!ft_strcmp(arg, "exit"))
		return (1);
	return (0);
}

int	do_builts_funct(t_data data, t_list **cmds, char *arg)
{
	change_negative((char **)(*cmds)->content);
	if (!ft_strcmp(arg, "echo"))
		return (echo((char **)(*cmds)->content));
	else if (!ft_strcmp(arg, "cd"))
		return (cd(data, *cmds));
	else if (!ft_strcmp(arg, "pwd"))
		return (pwd());
	else if (!ft_strcmp(arg, "export"))
		return (ft_export(data, (char **)(*cmds)->content));
	else if (!ft_strcmp(arg, "unset"))
		return (unset(data, (char **)(*cmds)->content));
	else if (!ft_strcmp(arg, "env"))
		return (env(data));
	else if (!ft_strcmp(arg, "exit"))
		ft_exit(data);
	return (0);
}

int	do_builtins(t_data data)
{
	char	*arg;
	t_list	**cmds;
	int		val;

	cmds = data.cmd_lst;
	val = -1;
	if (!(*cmds)->content[0])
		return (val);
	arg = (char *)(*cmds)->content[0];
	val = do_builts_funct(data, cmds, arg);
	if (val >= 0)
		set_value_env("?", ft_itoa(val), data);
	return (val);
}
