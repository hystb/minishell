/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 09:22:43 by ebillon           #+#    #+#             */
/*   Updated: 2023/01/16 13:34:05 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	cases(va_list *args, const char *text)
{
	if (*text == 'c')
		return (printf_putchar(va_arg(*args, int)));
	else if (*text == 'd' || *text == 'i')
		return (printf_putnbr(va_arg(*args, int)));
	else if (*text == 's')
		return (printf_putstr(va_arg(*args, char *)));
	else if (*text == 'p')
		return (printf_puthex_adrs(va_arg(*args, unsigned long)));
	else if (*text == 'u')
		return (printf_putnbr(va_arg(*args, unsigned int)));
	else if (*text == 'x')
		return (printf_puthex(va_arg(*args, unsigned int), 'a'));
	else if (*text == 'X')
		return (printf_puthex(va_arg(*args, unsigned int), 'A'));
	else if (*text == '%')
		return (printf_putchar('%'));
	else
		return (printf_putchar(*text));
}

int	printf_printf_aux(const char *text, int size, int temp, va_list *args)
{
	while (*text)
	{
		if (*text == '%' && *(text + 1) != '\0')
		{
			temp = cases(args, ++text);
			if (temp == -1)
				return (-1);
			size += temp;
		}
		else if (*text == '%' && *(text + 1) == '\0')
			return (size);
		else
		{
			temp = printf_putchar(*text);
			if (temp == -1)
				return (-1);
			size += temp;
		}
		text++;
	}
	va_end(*args);
	return (size);
}

int	ft_printf(const char *text, ...)
{
	int		size;
	int		temp;
	va_list	args;

	size = 0;
	temp = 0;
	if (!text)
		return (size);
	va_start(args, text);
	return (printf_printf_aux(text, size, temp, &args));
}
