/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:39:23 by ebillon           #+#    #+#             */
/*   Updated: 2023/03/21 11:21:22 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtins(t_list	**cmds)
{
	char	*arg;

	arg = (char *)(*cmds)->content[0];
	if (!ft_strncmp(arg, "echo", ft_strlen(arg)))
		return (1);
	else if (!ft_strncmp(arg, "cd", ft_strlen(arg)))
		return (1);
	else if (!ft_strncmp(arg, "pwd", ft_strlen(arg)))
		return (1);
	else if (!ft_strncmp(arg, "export", ft_strlen(arg)))
		return (1);
	else if (!ft_strncmp(arg, "unset", ft_strlen(arg)))
		return (1);
	else if (!ft_strncmp(arg, "env", ft_strlen(arg)))
		return (1);
	else if (!ft_strncmp(arg, "exit", ft_strlen(arg)))
		return (1);
	return (0);
}

int	do_builts_funct(t_data data, t_list **cmds, char *arg)
{
	if (!ft_strncmp(arg, "echo", ft_strlen(arg)))
		return (echo((char **)(*cmds)->content));
	else if (!ft_strncmp(arg, "cd", ft_strlen(arg)))
		return (cd(data, *cmds));
	else if (!ft_strncmp(arg, "pwd", ft_strlen(arg)))
		return (pwd());
	else if (!ft_strncmp(arg, "export", ft_strlen(arg)))
		return (ft_export(data, (char **)(*cmds)->content));
	else if (!ft_strncmp(arg, "unset", ft_strlen(arg)))
		return (unset(data, (char **)(*cmds)->content));
	else if (!ft_strncmp(arg, "env", ft_strlen(arg)))
		return (env(data));
	else if (!ft_strncmp(arg, "exit", ft_strlen(arg)))
		ft_exit(data);
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
