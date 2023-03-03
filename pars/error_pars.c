#include "../includes/minishell.h"

char	*input_error(char *in)
{
	int		i;

	i = 0;
	while (in[i])
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
	in = many_sign(in);
	in = sign_error(in, i);
	replace_comment(in, i);
	in = control_pipe(in, i);
	return (in);
}

char	*sign_error(char *in, int space)
{
	int	i;

	i = -1;
	while (in && in[++i])
	{
		if (in[i] == '<' || in[i] == '>')
		{
			while (in[i + 1] == ' ')
			{
				space++;
				i++;
			}
			if (space > 0 && (in[i + 1] == '<' || in[i + 1] == '>'))
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

char	*many_sign(char *in)
{
	int		count_less;
	int		count_more;
	int		i;

	count_less = 0;
	count_more = 0;
	i = 0;
	while (in[i])
	{
		if (in[i] == '<')
			count_less++;
		else if (in[i] == '>')
			count_more++;
		if ((in[i] == '<' || in[i] == '>') && (count_less > 2
				|| count_more > 1 || (count_more == 1 && count_less == 1)))	
			return (print_less_more_error(in, i + 1));
		else if (count_more + count_less >= 3)
		{
			print_undefine(UNCOMP_ERROR, NULL, "'\n", in[i]);
			free(in);
			return (NULL);
		}
		i++;
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
