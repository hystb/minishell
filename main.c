/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:58:37 by nmilan            #+#    #+#             */
/*   Updated: 2023/03/06 13:50:21 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/exec.h"
#include "includes/builtins.h"

int	main(int argc, char **argv, char **envp)
{
	char				*input;
	t_data				var_lst;
	t_list *tmp;
	//int i = 0;

	(void)argc;
	(void)argv;
	config_signal();
	var_lst.env_var = put_env(envp, var_lst);
	while (1)
	{
		input = make_input("minishell -> ", var_lst);
		if (input && input[0] != '\0')
		{
			var_lst.cmd_lst = put_input_lst(&input);
			tmp = *var_lst.cmd_lst;
			replace_env_var(var_lst);
			//t_list *it;
			//it = *var_lst.cmd_lst;
			do_exec(var_lst.cmd_lst, envp);
			/*while ((it))
			 {
			 	i = 0;
			 	while ((it)->content[i])
			 	{
			 		ft_printf("%s\n", (it)->content[i]);
			 		i++;
			 	}
			 	ft_printf("current : %p\n", it);
			 	ft_printf("prev : %p\n", (it)->previous);
			 	ft_printf("next : %p\n", (it)->next);
			 	it = (it)->next;
			}*/
			*var_lst.cmd_lst = tmp;
			ft_lstclear(var_lst.cmd_lst, del_free_content);
			free (var_lst.cmd_lst);
		}
		if (input)
			free(input);
	}
}
