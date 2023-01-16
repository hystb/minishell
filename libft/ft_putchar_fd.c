/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 18:01:23 by ebillon           #+#    #+#             */
/*   Updated: 2022/11/14 18:01:25 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
Write a char c, on the file descriptor fd.
*/

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
