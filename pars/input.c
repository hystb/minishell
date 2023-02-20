/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:58:37 by nmilan            #+#    #+#             */
/*   Updated: 2023/02/20 15:12:53 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*make_input(char *promp_name)
{
	char		*input;

	input = readline(promp_name);
	if (!input)
	{
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
		rl_on_new_line();
		write(STDIN_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
		return ;
}

void	config_terminal(void)
{
	/*struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ISIG);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);*/
	rl_catch_signals = 0;
}
