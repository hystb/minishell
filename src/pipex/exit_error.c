/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:41:16 by ebillon           #+#    #+#             */
/*   Updated: 2023/01/23 13:38:45 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

void	exit_error(void)
{
	perror("");
	exit(EXIT_FAILURE);
}

void	not_found_error(char *cmd)
{
	write(2, "pipex: ", 8);
	write(2, cmd, ft_strlen(cmd));
	write(2, ": command not found\n", 21);
	exit(127);
}

void	write_error(char *str)
{
	write(2, str, ft_strlen(str));
	exit(EXIT_FAILURE);
}
