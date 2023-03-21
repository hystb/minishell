/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:58:37 by nmilan            #+#    #+#             */
/*   Updated: 2023/03/21 12:20:38 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*make_input(char *promp_name, t_data var_lst)
{
	char		*input;

	g_signal_handle = 0;
	input = readline(promp_name);
	if (!input)
	{
		free_env_var(var_lst.env_var);
		rl_clear_history();
		ft_putstr_fd("\nexit\n", 2);
		exit(0);
	}
	if (ft_strlen(input) > 0)
		add_history(input);
	input = input_error(input, var_lst);
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
		if (g_signal_handle == 0)
		{
			write(STDIN_FILENO, "^C", 2);
			rl_replace_line("", 0);
			rl_on_new_line();
			write(STDIN_FILENO, "\n", 1);
			rl_redisplay();
		}
		if (g_signal_handle == 1)
			rl_redisplay();
		if (g_signal_handle > 2)
		{
			write(STDIN_FILENO, "\n", 1);
			close(g_signal_handle);
			exit(130);
		}
	}
	if (sig == SIGQUIT)
	{
		return ;
	}
}
