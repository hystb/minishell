#include "../includes/minishell.h"

void	replace_comment(char *in, int i)
{
	while (in && in[i])
	{
		if (in[i] == '#')
		{
			while (in[i] != '\0')
			{
				in[i++] = ' ';
				if (!in[i])
					return ;
			}
		}
		if (in[i] == ':')
		{
			while (in[i] && in[i] != '|')
				in[i++] = ' ';
			if (in[i] == '|')
				in[i] = ' ';
		}
		i++;
	}
}

char	*control_pipe(char *in, int i)
{
	int	is_write;

	while (in && in[i])
	{
		if (in[i] == '|')
		{
			i++;
			is_write = 0;
			while (in[i] && in[i] != '|')
			{
				if (in[i] != ' ')
					is_write++;
				i++;
			}
			i--;
			if (is_write == 0)
			{
				free(in);
				ft_putstr_fd(PIPE_ERROR, 2);
				return (NULL);
			}
		}
		i++;
	}
	return (in);
}
