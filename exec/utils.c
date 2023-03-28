/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:43:17 by ebillon           #+#    #+#             */
/*   Updated: 2023/03/28 13:44:06 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*check_var(char *arg, t_data var_lst, int j, int i)
{
	int		is_sp_quote;
	char	*var;

	var = arg;
	is_sp_quote = 0;
	while (arg[++i])
	{
		if (arg[i] == '\'' && is_sp_quote == 0)
			is_sp_quote = 1;
		else if (arg[i] == '\'' && is_sp_quote == 1)
			is_sp_quote = 0;
		if (arg[i] == '$' && is_sp_quote == 0)
		{
			j = i + 1;
			while (arg[i] != ' ' && arg[i] != '\f' && arg[i] != '\n'
				&& arg[i] != '\t' && arg[i] != '\v' && arg[i] != '\r'
				&& arg[i] && arg[i] != '"')
				i++;
			var = ft_substr(arg, j, i - j);
			var = sub_env_var(var, arg, j - 1, var_lst);
			return (var);
		}
	}
	return (var);
}

void	add_pids(pid_t value, t_listpids **list, t_data data)
{
	t_listpids	*new;
	t_listpids	*i;

	new = malloc(sizeof(t_listpids));
	if (!new)
		write_error("Memory allocation error !", data);
	new->pid = value;
	new->next = NULL;
	i = *list;
	if (i)
	{
		while (i->next)
			i = i->next;
		i->next = new;
	}
	else
		*list = new;
}

int	ft_strcmp(char *a, char *b)
{
	int	i;

	if (!a || !b)
		return (0);
	i = 0;
	while (a[i])
	{
		if (a[i] != b[i])
			break ;
		i++;
	}
	return (a[i] - b[i]);
}

int	is_blank(char *str)
{
	if (!str[0])
		return (1);
	return (0);
}
