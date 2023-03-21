/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:39:23 by ebillon           #+#    #+#             */
/*   Updated: 2023/03/21 15:02:57 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	go_to(t_data data, char *dest)
{
	char	*path_old;

	path_old = get_item_env(data, "PWD");
	if (chdir(dest) == -1)
	{
		perror("");
		return (1);
	}
	set_value_env("OLDPWD", ft_strdup(path_old), data);
	set_value_env("PWD", ft_strdup(dest), data);
	return (0);
}

int	args_len(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	cd(t_data data, t_list *cmds)
{
	char	**args;
	char	*path;

	args = (char **)cmds->content;
	if (args_len(args) == 1)
	{
		path = get_item_env(data, "HOME");
		if (!path)
		{
			write(2, "minishell: cd: HOME not set\n", 29);
			return (1);
		}
	}
	else if (!ft_strncmp(args[1], "-", ft_strlen(args[1])))
		path = get_item_env(data, "OLDPWD");
	else
		path = args[1];
	return (go_to(data, path));
}
