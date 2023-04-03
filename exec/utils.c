/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/21 13:43:17 by ebillon           #+#    #+#             */
/*   Updated: 2023/04/03 14:59:54 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	**free_env_case(char **a, char **b, char **res, int j)
{
	res[j] = NULL;
	free(a);
	free(b);
	return (res);
}

void	restore_counter(int *a, int *b)
{
	*a = 0;
	*b = 0;
}
