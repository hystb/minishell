/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:58:37 by nmilan            #+#    #+#             */
/*   Updated: 2023/02/22 15:00:46 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"
#include "includes/exec.h"
#include "includes/builtins.h"

// int main(int argc, char **argv, char **env)
// {
// 	printf("je suis dans minishle\n");
// 	(void) argc;
// 	(void) argv;
// 	char *cmds[] = {"./minishell", NULL};
// 	printf("%d\n",execve(cmds[0], cmds + 1, env));
// }

int	main(int argc, char **argv, char **envp)
{
	char				*input;
	t_list				**lst_cmd;
	t_list *tmp;
	int i = 0;

	(void)argc;
	(void)argv;
	config_signal();
	while (1)
	{
		input = make_input("minishell -> ");
		if (input[0] != '\0')
		{
			lst_cmd = put_input_lst(&input, envp);
			tmp = *lst_cmd;
			// faire l'exec la
			t_list **it;
			it = lst_cmd;
			//do_exec(lst_cmd, envp); // partie exec
			 while ((*it))
			 {
			 	i = 0;
			 	while ((*it)->content[i])
			 	{
			 		ft_printf("%s\n", (*it)->content[i]);
			 		i++;
			 	}
			 	ft_printf("current : %p\n", *it);
			 	ft_printf("prev : %p\n", (*it)->previous);
			 	ft_printf("next : %p\n", (*it)->next);
			 	*it = (*it)->next;
			 }
			*lst_cmd = tmp;
			ft_lstclear(lst_cmd, del_free_content);
			free (lst_cmd);
		}
		if (input)
			free(input);
	}
}
