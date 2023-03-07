/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 16:41:46 by ebillon           #+#    #+#             */
/*   Updated: 2023/03/07 14:15:42 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
Compare *s1 and *s2 and return *s1 - *s2 when reach end of file or different.
*/

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	if (!s1 || !s2)
		return (0);
	while (*s1 == *s2 && n - 1 && *s1 && *s1)
	{
		n--;
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}
