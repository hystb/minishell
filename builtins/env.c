/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:39:23 by ebillon           #+#    #+#             */
/*   Updated: 2023/03/21 14:37:52 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	env(t_data data)
{
	t_env	*temp;

	temp = *(data.env_var);
	while (temp)
	{
		if (ft_strncmp(temp->name_var, "?", ft_strlen(temp->name_var)))
			printf("%s=%s\n", temp->name_var, temp->content_var);
		temp = temp->next;
	}
	return (0);
}
