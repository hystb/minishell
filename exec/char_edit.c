/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_edit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 12:56:09 by nmilan            #+#    #+#             */
/*   Updated: 2023/03/29 13:10:45 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*rechange_target(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == -6)
			str[i] = '<';
		if (str[i] == -7)
			str[i] = '>';
		i++;
	}
	return (str);
}

void	change_negative(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		rechange_target(tab[i]);
		i++;
	}
}
