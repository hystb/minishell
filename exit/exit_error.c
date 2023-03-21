/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:41:16 by ebillon           #+#    #+#             */
/*   Updated: 2023/03/21 12:25:36 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_error(t_data data)
{
	perror("");
	free_data(data);
	exit(EXIT_FAILURE);
}

void	not_found_error(char *cmd, t_data data)
{
	write(2, "minishell: ", 11);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 21);
	free_data(data);
	exit(127);
}

void	write_error(char *str, t_data data)
{
	write(2, str, ft_strlen(str));
	free_data(data);
	exit(EXIT_FAILURE);
}
