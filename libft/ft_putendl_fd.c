/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:02:08 by ebillon           #+#    #+#             */
/*   Updated: 2022/11/14 18:02:10 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Write the *s on the fd and add a '\n'
*/

void	ft_putendl_fd(char *s, int fd)
{
	if (s)
		ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
