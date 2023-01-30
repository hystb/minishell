/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:51:19 by nmilan            #+#    #+#             */
/*   Updated: 2023/01/30 14:04:28 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_space_pipe(char *input)
{
	int	i;

	i = 0;
	if (need_space(input))
		return ;
	while (input[i])
	{
		
	}
}

int	need_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (i > 0 && input[i] == '|' && (input[i - 1] != ' '
				|| input[i + 1] != ' '))
			return (0);
	}
}
