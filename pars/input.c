/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:58:37 by nmilan            #+#    #+#             */
/*   Updated: 2023/02/20 13:19:14 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*make_input(char *promp_name, t_data var_lst)
{
	char		*input;

	input = readline(promp_name);
	if (!input)
	{
		free_env_var(var_lst.env_var);
		ft_putstr_fd("\nexit\n", 2);
		exit(1);
	}
	if (ft_strlen(input) > 0)
		add_history(input);
	return (input);
}

void	config_signal(void)
{
	struct sigaction	sig;

	rl_catch_signals = 0;
	sig.sa_handler = &handle_signal;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &sig, NULL) == -1)
		perror("Error, SIGINT not define\n");
	if (sigaction(SIGQUIT, &sig, NULL) == -1)
		perror("Error, SIGQUIT not define\n");
}

void	handle_signal(int sig)
{
	
	if (sig == SIGINT)
	{
		write(STDIN_FILENO, "^C", 2);
		rl_on_new_line();
		write(STDIN_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		return ;
	}
}
