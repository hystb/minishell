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
	char	*input;
	t_list	**lst_cmd;
	int i = 0;

	(void)argc;
	(void)argv;
	while (1)
	{
		input = readline("minishell -> ");
		if (!input)
		{
			ft_putstr_fd("\nexit", 2);
			exit(1);
		}
		lst_cmd = put_input_lst(&input);
		if (input)
			free(input);
		/*while (*lst_cmd)
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
		}*/
		ft_lstclear(lst_cmd, del_free_content);
		free (lst_cmd);
		return (0);
	}
}
