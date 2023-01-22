/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:21:13 by ebillon           #+#    #+#             */
/*   Updated: 2023/01/17 15:54:15 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main(int argc, char **argv, char **envp)
{
    char    *input;
    t_list  **lst_cmd;
    (void)argc;
    (void)argv;
    while (1)
    {
        input = readline("minishell >");
        if (!input)
        {
            ft_putstr_fd("Mem alloc failed", 2);
            exit(1);
        }
        lst_cmd = put_input_lst(input);
    }
    
}