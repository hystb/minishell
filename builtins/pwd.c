/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:34:28 by nmilan            #+#    #+#             */
/*   Updated: 2023/02/20 14:54:13 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/builtins.h"

void	pwd(void)
{
	char *path;

	path = getcwd(NULL, 0);
	if(!path)
	{
		perror("path not found\n");
		return ;
	}
	ft_printf("%s\n", path);
	free(path);
}