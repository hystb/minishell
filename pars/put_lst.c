/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:07:01 by nmilan            #+#    #+#             */
/*   Updated: 2023/03/30 14:59:40 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	**put_input_lst(char **input)
{
	t_list	**cmd;
	t_cmds	data_cmd;

	cmd = malloc(sizeof(t_list *));
	if (!cmd)
	{
		ft_putstr_fd("Mem alloc failed", 2);
		free(input[0]);
		input[0] = NULL;
		return (NULL);
	}
	*cmd = NULL;
	prepare_input(input[0], &data_cmd);
	prepare_split(input, 0, 0, -1);
	if (!input[0])
	{
		free (cmd);
		return (NULL);
	}
	input[0] = add_space_pipe(input[0]);
	put_in_lst(input[0], cmd, data_cmd);
	return (cmd);
}

void	put_in_lst(char *input, t_list **cmd, t_cmds data_cmd)
{
	char	***map_cmd;
	int		i;

	if (!input)
		return ;
	i = 0;
	map_cmd = malloc(sizeof(char **) * \
	(2 + data_cmd.nb_sign * 2 + data_cmd.nb_pipes * 2));
	if (!map_cmd)
	{
		map_cmd = NULL;
		return ;
	}
	split_map(map_cmd, input);
	replace_pipe_in_quote(map_cmd);
	while (map_cmd && map_cmd[i])
	{
		ft_lstadd_back(cmd, ft_lstnew(map_cmd[i]));
		i++;
	}
	free(map_cmd);
}

void	split_map(char ***map_cmd, char *input)
{
	char	**splited;
	int		i;
	int		last_splited;

	i = 0;
	last_splited = 0;
	splited = ft_split(input, ' ');
	if (!splited)
		return ;
	change_split(splited);
	while (splited[i])
	{
		if (ft_memchr(splited[i], '|', ft_strlen(splited[i])))
		{
			make_map_pipe(map_cmd, splited, i, last_splited);
			last_splited = i + 1;
		}
		i++;
	}
	make_map(map_cmd, splited, i - 1, last_splited);
	free(splited);
}

void	prepare_input(char *input, t_cmds *cmd)
{
	int	i;

	i = 0;
	cmd->sp_quote_f = 0;
	cmd->sp_quote_s = 0;
	cmd->db_quote_f = 0;
	cmd->db_quote_s = 0;
	cmd->nb_pipes = 0;
	cmd->nb_sign = 0;
	while (input[i])
	{
		if (input[i] == '|')
			cmd->nb_pipes++;
		if (input[i] == '\'' && cmd->sp_quote_s == cmd->sp_quote_f)
			cmd->sp_quote_s++;
		else if (input[i] == '\'' && cmd->sp_quote_s != cmd->sp_quote_f)
			cmd->sp_quote_f++;
		if (input[i] == '"' && cmd->db_quote_s == cmd->db_quote_f)
			cmd->db_quote_s++;
		else if (input[i] == '"' && cmd->db_quote_s != cmd->db_quote_f)
			cmd->db_quote_f++;
		if (input[i] == '<' || input[i] == '>')
			cmd->nb_sign++;
		i++;
	}
}

void	prepare_split(char **input, char c, int i, int index)
{
	while (input[0][i])
	{
		if (input[0][i] == '\'' || input[0][i] == '"')
		{
			if (!c)
			{
				c = input[0][i];
				index = i;
			}
			else if (input[0][i] == c)
				c = 0;
		}		
		if (index != -1 && c == 0)
		{
			change_space(input[0], i, index, 1);
			index = -1;
		}
		i++;
	}
	if (c)
	{
		free(input[0]);
		input[0] = NULL;
		ft_putstr_fd(ERROR_QUOTE, 2);
	}
}
