/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:21:13 by ebillon           #+#    #+#             */
/*   Updated: 2023/01/30 15:40:51 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"


/* todo

	fix all the tube issues by passing data
	and fix tube for redirections.

	si << en dernier alors pas l'afficher dans le terminal
	here doc fucking issues
*/

int main(int argc, char **args, char **env)
{
	// t_list	**list;
	// t_list 	*part;

	// part = ft_lstnew()
	
	char *cmds[10] = {"< 1", "cat -e", "> 2", NULL};
	// do_input("1");
	// do_heredoc("ko");
	do_commands(cmds, env);
	// printf("bonjour\n");
}
