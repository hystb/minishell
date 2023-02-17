/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:58:37 by nmilan            #+#    #+#             */
/*   Updated: 2023/02/06 17:11:13 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char				*input;
	t_list				**lst_cmd;
	t_list *tmp;
	int i = 0;

	(void)argc;
	(void)argv;
	config_terminal();
	config_signal();
	while (1)
	{
		input = make_input("minishell -> ");
		lst_cmd = put_input_lst(&input);
		tmp = *lst_cmd;
		if (input)
			free(input);
		while (*lst_cmd)
		{
			i = 0;
			while ((*lst_cmd)->content[i])
			{
				ft_printf("%s\n", (*lst_cmd)->content[i]);
				i++;
			}
			ft_printf("current : %p\n", *lst_cmd);
			ft_printf("prev : %p\n", (*lst_cmd)->previous);
			ft_printf("next : %p\n", (*lst_cmd)->next);
			*lst_cmd = (*lst_cmd)->next;
		}
		*lst_cmd = tmp;
		ft_lstclear(lst_cmd, del_free_content);
		free (lst_cmd);
	}
}
