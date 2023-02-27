/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/22 12:12:25 by nmilan            #+#    #+#             */
/*   Updated: 2023/02/22 13:56:32 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*is_env_vars(char *arg)
{
	int		is_sp_quote;
	int		i;
	char	*var;
	int		j;

	is_sp_quote = 0;
	i = -1;
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
			sub_env_var(var, arg, j - 1, i - j);
			return (var);
		}
	}
}

void	sub_env_var(char *var, char *arg, int start, int size)
{
	
}
