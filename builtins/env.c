/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethaaalpha <ethaaalpha@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:39:23 by ebillon           #+#    #+#             */
/*   Updated: 2023/03/16 15:31:06 by ethaaalpha       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env(t_data data)
{
	t_env	*temp;

	temp = *(data.env_var);
	while (temp)
	{
		printf("%s=%s\n", temp->name_var, temp->content_var);
		temp = temp->next;
	}
	return (0);
}
