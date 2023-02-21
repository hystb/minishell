/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:58:37 by nmilan            #+#    #+#             */
/*   Updated: 2023/02/20 13:57:52 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/exec.h"
#include "includes/builtins.h"

int	main(int argc, char **argv, char **envp)
{
	char				*input;
	t_list				**lst_cmd;
	t_list *tmp;
	// int i = 0;

	(void)argc;
	(void)argv;
	config_signal();
	while (1)
	{
		input = make_input("minishell -> ");
		lst_cmd = put_input_lst(&input);
		tmp = *lst_cmd;
		if (input)
			free(input);
		// faire l'exec la
		if ((*lst_cmd)->content[0])
			do_exec(lst_cmd, envp);
		// while (*lst_cmd)
		// {
		// 	i = 0;
		// 	while ((*lst_cmd)->content[i])
		// 	{
		// 		ft_printf("%s\n", (*lst_cmd)->content[i]);
		// 		i++;
		// 	}
		// 	ft_printf("current : %p\n", *lst_cmd);
		// 	ft_printf("prev : %p\n", (*lst_cmd)->previous);
		// 	ft_printf("next : %p\n", (*lst_cmd)->next);
		// 	*lst_cmd = (*lst_cmd)->next;
		// }
		*lst_cmd = tmp;
		ft_lstclear(lst_cmd, del_free_content);
		free (lst_cmd);
	}
}
