#include "../includes/minishell.h"

int	got_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int check_str(char *str)
{
	int	i;
	
	i = 0;
	while (str[i])
	{
		if ((!ft_isalnum(str[i])) && str[i] != '_')
		{
			write(STDERR_FILENO, "minishell: export: `", 20);
			write(STDERR_FILENO, &str[i], 1);
			write(STDERR_FILENO, "': not a valid identifier\n", 27);
			return (1);
		}
		i++;
	}
	return (0);
}

char	*get_key(char *str, int *i)
{
	if (str[*i] == '=')
	{
		check_str(&str[*i]);
		return (NULL);
	}
	while (str[*i] != '=')
		*i += 1;
	str[*i] = '\0';
	if (check_str(str))
		return (NULL);
	return (str);
}

int	do_export(t_data data, char *str)
{
	char	*value;
	int		i;
	char	*key;

	i = 0;
	value = "";
	if (got_equal(str) == 0)
	{
		if (check_str(str))
			return (1);
		set_value_env(str, ft_strdup(value), data);
	}
	else
	{
		key = get_key(str, &i);
		if (!key)
			return (1);
		set_value_env(key, ft_strdup(&str[i + 1]), data);
	}
	return (0);
}

int	ft_export(t_data data, char **args)
{
	int	i;
	int	val;

	val = 0;
	i = 1;
	if (args_len(args) == 1)
		val += do_export_nargs(data);
	else
	{
		while (args[i])
		{
			val += do_export(data, args[i]);
			i++;
		}
	}
	if (val)
		return (1);
	return (0);
}
