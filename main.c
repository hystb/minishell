/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:58:37 by nmilan            #+#    #+#             */
/*   Updated: 2023/03/21 13:00:11 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_signal_handle;

int	main(int argc, char **argv, char **envp)
{
	char				*input;
	t_data				var_lst;

	(void)argc;
	(void)argv;
	g_signal_handle = 0;
	config_signal();
	var_lst.env_var = put_env(envp, var_lst);
	var_lst.lst_pids = NULL;
	while (1)
	{
		input = make_input("minishell -> ", var_lst);
		if (input && input[0] != '\0')
		{
			var_lst.cmd_lst = put_input_lst(&input);
			if (!var_lst.cmd_lst)
				continue ;
			replace_env_var(var_lst);
			do_exec(var_lst);
			ft_lstclear(var_lst.cmd_lst, del_free_content);
			free (var_lst.cmd_lst);
		}
		if (input)
			free(input);
	}
}
