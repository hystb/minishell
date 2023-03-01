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
		if (in[0] == ':' || '#')
		{
			free (in);
			return (NULL);
		}
		i++;
	}
	in = sign_error(in);
	return (in);
}

char	*sign_error(char *in)
{
	int	i;

	i = 0;
	many_sign(in);
	while (in && in[i])
	{
		if (in[i] == '<' || in[i] == '>')
		{
			while (in[i + 1] == ' ')
				i++;
			if (in[i + 1] == '\0')
			{
				ft_putstr_fd(NEWLINE_ERROR, 2);
				free(in);
				return (NULL);
			}
		}
		i++;
	}
	return (in);
}

char	*many_sign(char *in)
{
	int	count_less;
	int	count_more;
	int	i;

	count = 0;
	i = 0;
	while (in[i] &&)
	{
		
	}
	
}