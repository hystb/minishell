/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:58:37 by nmilan            #+#    #+#             */
/*   Updated: 2023/03/07 14:22:22 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"


// faire les env avec les trucs
int	g_signal_handle;

int	main(int argc, char **argv, char **envp)
{
	char				*input;
	t_data				var_lst;
	t_list *tmp;
	// int i = 0;

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
			tmp = *var_lst.cmd_lst;
			replace_env_var(var_lst);
			// t_list *it;
			// it = *var_lst.cmd_lst;
			do_exec(var_lst);
			// while ((it))
			//  {
			 	// i = 0;
			 	// while ((it)->content[i])
			 	// {
			 		// ft_printf("%s\n", (it)->content[i]);
			 		// i++;
			 	// }
			 	// ft_printf("current : %p\n", it);
			 	// ft_printf("prev : %p\n", (it)->previous);
			 	// ft_printf("next : %p\n", (it)->next);
			 	// it = (it)->next;
			// }
			*var_lst.cmd_lst = tmp;
			ft_lstclear(var_lst.cmd_lst, del_free_content);
			free (var_lst.cmd_lst);
		}
		if (input)
			free(input);
	}
}
