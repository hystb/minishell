/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 10:58:37 by nmilan            #+#    #+#             */
/*   Updated: 2023/03/30 12:57:30 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_signal_handle;

void	define_basic(t_data data, int argc, char **argv)
{
	int	lv;

	(void)argc;
	(void)argv;
	data.cmd_lst = NULL;
	if (!get_item_env(data, "SHLVL"))
		lv = 0;
	else
		lv = ft_atoi(get_item_env(data, "SHLVL"));
	if (lv < 1)
		lv = 0;
	if (lv > 998)
	{
		lv = 0;
		write(STDIN_FILENO, SHLVL_ERROR, 58);
	}
	set_value_env("PWD", getcwd(NULL, 0), data);
	set_value_env("SHLVL", ft_itoa(lv + 1), data);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_data	var_lst;

	g_signal_handle = 0;
	var_lst.cmd_lst = NULL;
	config_signal();
	var_lst.env_var = put_env(envp, var_lst);
	var_lst.lst_pids = NULL;
	define_basic(var_lst, argc, argv);
	while (1)
	{
		input = make_input("minishell -> ", var_lst);
		if (input && input[0] != '\0')
		{
			var_lst.cmd_lst = put_input_lst(&input);
			if (!var_lst.cmd_lst)
				continue ;
			replace_env_var(var_lst);
			do_exec(var_lst, var_lst.cmd_lst, 0, NULL);
			ft_lstclear(var_lst.cmd_lst, del_free_content);
			free (var_lst.cmd_lst);
		}
		if (input)
			free(input);
	}
}
