/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:07:01 by nmilan            #+#    #+#             */
/*   Updated: 2023/01/23 14:55:00 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	**put_input_lst(char *input)
{
	t_list	**cmd;
	t_cmds	data_cmd;

	cmd = malloc(sizeof(t_list *));
	if (!cmd)
	{
		ft_putstr_fd("Mem alloc failed", 2);
		free(input);
		exit(1);
	}
	*cmd = NULL;
	prepare_input(input, &data_cmd);
	put_in_lst(input, cmd, data_cmd);
	return (cmd);
}

void	put_in_lst(char *input, t_list **cmd, t_cmds data_cmd)
{
	char	***map_cmd;
	int		i;

	i = 0;
	//ft_printf("%d\n", data_cmd.nb_pipes);
	map_cmd = malloc(sizeof(char **) * (2 + data_cmd.nb_pipes * 2));
	if (!map_cmd)
	{
		//put exit function
		exit(1);
	}
	split_map(map_cmd, input, data_cmd);
	while (map_cmd[i])
	{
		ft_printf("ok\n");
		if (!*cmd)
			*cmd = ft_lstnew(map_cmd[i]);
		else
			ft_lstadd_back(cmd, ft_lstnew(map_cmd[i]));
		i++;
	}
}

void	split_map(char ***map_cmd, char *input, t_cmds data)
{
	char	**splited;
	int		i;
	int		j;
	int		last_splited;

	i = 0;
	j = 0;
	last_splited = 0;
	splited = ft_split(input, ' ');
	while (splited[i])
	{
		if (data.sp_quote_s == 0 || data.db_quote_s == 0)
		{
			if (ft_memchr(splited[i], '|', ft_strlen(splited[i])))
			{
				ft_printf("OK\n");
				make_map_pipe(map_cmd, splited, i, last_splited);
				last_splited = i + 1;
			}
		}
		i++;
	}
	make_map(map_cmd, splited, i - 1, last_splited);
	free(splited);
}

void	prepare_input(char *input, t_cmds *data_cmd)
{
	int	i;

	i = 0;
	data_cmd->sp_quote_f = 0;
	data_cmd->sp_quote_s = 0;
	data_cmd->db_quote_f = 0;
	data_cmd->db_quote_s = 0;
	data_cmd->nb_pipes = 0;
	while (input[i])
	{
		if (input[i] == '|')
			data_cmd->nb_pipes++;
		if (input[i] == '\'' && data_cmd->sp_quote_s == data_cmd->sp_quote_f)
			data_cmd->sp_quote_s++;
		if (input[i] == '\'' && data_cmd->sp_quote_s != data_cmd->sp_quote_f)
			data_cmd->sp_quote_f++;
		if (input[i] == '\"' && data_cmd->sp_quote_s == data_cmd->sp_quote_f)
			data_cmd->db_quote_s++;
		if (input[i] == '\"' && data_cmd->sp_quote_s != data_cmd->sp_quote_f)
			data_cmd->db_quote_f++;
		i++;
	}
	if (data_cmd->db_quote_s != data_cmd->db_quote_f
		|| data_cmd->sp_quote_s != data_cmd->sp_quote_f)
		ft_putstr_fd("error to put", 2); //error to put     
}
