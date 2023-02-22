/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:07:01 by nmilan            #+#    #+#             */
/*   Updated: 2023/02/22 15:29:01 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	**put_input_lst(char **input, char **envp)
{
	t_list	**cmd;
	t_cmds	data_cmd;

	cmd = malloc(sizeof(t_list *));
	if (!cmd)
	{
		ft_putstr_fd("Mem alloc failed", 2);
		free(input[0]);
		exit(1);
	}
	*cmd = NULL;
	prepare_input(input[0], &data_cmd);
	input[0] = add_pipe_sign(input[0]);
	input[0] = add_space_pipe(input[0]);
	prepare_split(input[0]);
	put_in_lst(input[0], cmd, data_cmd);
	//put_env(envp, *cmd);
	return (cmd);
}

void	put_in_lst(char *input, t_list **cmd, t_cmds data_cmd)
{
	char	***map_cmd;
	int		i;

	i = 0;
	map_cmd = malloc(sizeof(char **) * \
	(2 + data_cmd.nb_sign * 2 + data_cmd.nb_pipes * 2));
	if (!map_cmd)
	{
		//put exit function
		exit(1);
	}
	split_map(map_cmd, input, data_cmd);
	while (map_cmd[i])
	{
		if (!*cmd)
			*cmd = ft_lstnew(map_cmd[i]);
		else
			ft_lstadd_back(cmd, ft_lstnew(map_cmd[i]));
		i++;
	}
	free(map_cmd);
}

void	split_map(char ***map_cmd, char *input, t_cmds data)
{
	char	**splited;
	int		i;
	int		last_splited;
	int		last_pipe;

	(void) data;
	i = 0;
	last_splited = 0;
	last_pipe = 0;
	splited = ft_split(input, ' ');
	change_split(splited);
	while (splited[i])
	{
		ft_printf("input %s\n", splited [i]);
		if (ft_memchr(splited[i], '|', ft_strlen(splited[i])) && last_pipe == 0)
		{
			make_map_pipe(map_cmd, splited, i, last_splited);
			last_splited = i + 1;
			last_pipe = 1;
		}
		else if (last_pipe == 1)
		{
			last_pipe = 0;
			last_splited++;
			free(splited[last_splited - 1]);
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

void	prepare_split(char *input)
{
	char	c;
	int		i;
	int		index;

	c = 0;
	i = 0;
	index = 0;
	while (input[i])
	{
		if (input[i] == '\'' || input[i] == '"')
		{
			if (!c)
			{
				c = input[i];
				index = i;
			}
			else if (input[i] == c)
				c = 0;
		}		
		if (index != 0 && c == 0)
		{
			change_space(input, i, index, 1);
			index = 0;
		}
		i++;
	}
	if (c)
		ft_putstr_fd("error tu put", 2);//error to manage
}
