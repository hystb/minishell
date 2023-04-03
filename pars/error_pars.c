/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:22:33 by nmilan            #+#    #+#             */
/*   Updated: 2023/04/03 15:02:13 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*input_error(char *in, t_data var_lst)
{
	int		i;

	i = 0;
	while (in && in[i])
	{
		if (in[i] == '!')
		{
			if (in[i + 1] == '\0')
			{
				free (in);
				return (NULL);
			}
		}
		i++;
	}
	i = 0;
	in = replace_tab_and_printable(in);
	in = many_sign(in, 0, 0, 0);
	in = sign_error(in, i, -1, 0);
	in = control_pipe(in, i);
	in = empty_before_pipe(in, 0, 0);
	if (!in)
		set_value_env("?", ft_strdup("2"), var_lst);
	return (in);
}

char	*sign_error(char *in, int space, int i, char c)
{
	while (in && in[++i])
	{
		space = 0;
		c = is_quote_in_sign(c, in[i]);
		if ((in[i] == '<' || in[i] == '>') && c == 0)
		{
			while (in[i + 1] == ' ')
			{
				space++;
				i++;
			}
			if (space > 0 && (in[i + 1] == '<' || in[i + 1] == '>'
					|| in[i + 1] == '|'))
			{
				print_undefine(UNCOMP_ERROR, NULL, "'\n", in[i + 1]);
				return (free(in), NULL);
			}
			if (in[i + 1] == '\0')
			{
				ft_putstr_fd(NEWLINE_ERROR, 2);
				return (free(in), NULL);
			}
		}
	}
	return (in);
}

char	*many_sign(char *in, int count_less, int count_more, int c)
{
	int		i;

	i = -1;
	while (in && in[++i])
	{
		if ((in[i] == '\'' || in[i] == '"') && c == 0)
			c = in[i];
		else if (in[i] == c && c != 0)
			c = 0;
		if (in[i] == '<' && c == 0)
			count_less++;
		else if (in[i] == '>' && c == 0)
			count_more++;
		if ((in[i] == '<' || in[i] == '>') && (count_less > 1 || count_more > 1
				|| (count_more == 1 && count_less == 1)) && c == 0)
			return (print_less_more_error(in, i + 1));
		else if (count_more + count_less >= 3)
		{
			print_undefine(UNCOMP_ERROR, NULL, "'\n", in[i]);
			return (free(in), NULL);
		}
		if (in[i] != '>' && in[i] != '<' && in[i] != ' ')
			restore_counter(&count_less, &count_more);
	}
	return (in);
}

char	*print_less_more_error(char *in, int i)
{
	char	res[4];

	ft_bzero(res, 4);
	in = print_less_error(in, i, res);
	if (in && in[i++] == '<')
	{
		res[0] = '<';
		if (in[i] == '>')
			res[1] = '>';
		else if (in[i++] == '<')
		{
			res[1] = '<';
			if (in[i] == '<')
			{
				res[2] = '<';
				res[3] = '\0';
			}
		}
		else
			res[2] = '\0';
		print_undefine(UNCOMP_ERROR, res, "'\n", 0);
		free(in);
		return (NULL);
	}
	return (in);
}

char	*print_less_error(char *in, int i, char *res)
{
	if (in[i++] == '>')
	{
		res[0] = '>';
		if (in[i++] == '>')
		{
			res[1] = '>';
			res[2] = '\0';
		}
		else
			res[1] = '\0';
		print_undefine(UNCOMP_ERROR, res, "'\n", 0);
		free(in);
		return (NULL);
	}
	return (in);
}
