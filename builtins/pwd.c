/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:34:28 by nmilan            #+#    #+#             */
/*   Updated: 2023/03/28 16:26:36 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("path not found\n");
		return (EXIT_FAILURE);
	}
	ft_printf("%s\n", path);
	free(path);
	return (EXIT_SUCCESS);
}
