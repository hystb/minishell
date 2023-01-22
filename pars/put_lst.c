/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:21:13 by nmilan            #+#    #+#             */
/*   Updated: 2023/01/17 15:54:15 by nmilan           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list  **lst_cmd(char *input)
{
    t_list  **cmd;
    t_cmds  data_cmd;

    cmd = malloc(sizeof(t_list *));
    if (!cmd)
    {
        ft_putstr_fd("Mem alloc failed", 2);
        free(input);
        exit(1);
    }
    prepare_input(input, &data_cmd);
    put_in_lst(input, cmd, data_cmd);
}

void    put_in_lst(char * input, t_list **cmd, t_cmds data_cmd)
{
    char    ***map_cmd;
    map_cmd = malloc(sizeof(char **) * (2 + data_cmd.nb_pipes * 2));
    if (!map_cmd)
    {
        //put exit function
        exit(1);
    }

    
}

void    split_map(char ***map_cmd, char *input, t_cmds data)
{
    char    **splited;
    int     i;

    i = 0;
    splited = ft_split(input, ' ');
    while (splited[i])
    {    
        if (data.sp_quote_s == 0 || data.db_quote_s == 0)
        {
            if (/* condition */)
            {
                /* code */
            }
        
        }
    }
    
}

void    prepare_input(char *input, t_cmds *data_cmd)
{
    int i;

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
        || data_cmd->db_quote_s != data_cmd->db_quote_f)
        ft_putstr_fd("error to put", 2); //error to put     
}
