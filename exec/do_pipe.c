/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 15:49:52 by ebillon           #+#    #+#             */
/*   Updated: 2023/02/22 13:41:23 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"

/* check about parent activity and redirections possibilites */
void	pre_redirect(t_list *cmds, int lst_len, char **env, t_redirect *data)
{
	int	value;

	// printf("je pre_redirect avec %s | %d\n", (char *) cmds->content[0], data->tube_out);
	if (ft_strncmp((char *)cmds->content[0], "|", 1) == 0)
	{
		pre_redirect(cmds->next, lst_len - 1, env, data);
		return ;
	}
	value = do_redirection(cmds, data);
	if (value)
	{
		lst_len -= value;
		if (lst_len >= 1)
			pre_redirect(cmds + value, lst_len, env, data); //handle + value as ->next->next
		close_fd(data->tube_out);
	}
	else
	{
		// if (data->tube_out >= 0)
		// 	printf("\n");
		// 	// dup2(data->tube_out, STDIN_FILENO); //-> fait crash le shell
		// else
		// {
		// 	// dup2(0, STDIN_FILENO);
		// }
		redirect(cmds, lst_len, env, data);
		close_fd(data->tube_out);
	}
}

/* do the loop that execute and pipe the command, then return the fd filled */
void	redirect(t_list *cmds, int argc, char **env, t_redirect *data)
{
	static int	i = 0;
	int			tube[2];
	pid_t		pid;

	if (pipe(tube) == -1)
		exit_error();
	pid = fork();
	if (pid == -1)
		exit_error();
	data->pids[i++] = pid;
	if (pid == 0)
		do_child(tube, cmds, env, data);
	else
	{
		close_fd(tube[1]);
		if (argc > 1)
		{
			data->tube_out = tube[0];
			pre_redirect(cmds->next, argc - 1, env, data);
		}
		else
			fill_redirect(tube[0], &i, data);
	}
}

void	fill_redirect(int fd, int *i, t_redirect *data)
{
	int	*temp;

	close_fd(data->tube_out);
	data->fd = fd;
	*i = 0;
}

// go and make the redirection ( mettre en place les buildints ici aussi) passer a la commande suivante si echec
/* change here by passing the cmd */
void	do_child(int *tube, t_list *cmds, char **env, t_redirect *data)
{
	char	**args;

	// args = ft_split(*cmds, ' ');
	args = (char **)cmds->content;
	dup2(tube[1], STDOUT_FILENO);
	do_execute(args, env, tube, data);
}

/* do the command */
void	do_execute(char **args, char **env, int *tube, t_redirect *data)
{
	char	*cmd;

	cmd = args[0];
	if (data->tube_out >= 0)
		dup2(data->tube_out, STDIN_FILENO);
	// do heredoc check in.
	if (data->tube_out == -2)
		return(free(args));
	if (access(cmd, O_RDONLY) == -1)
		cmd = get_path(*args, env);
	else
		cmd = ft_strdup(*args);
	close_fd(tube[0]);
	//do here for the input and ouput things
	if (cmd)
	{
		if (execve(cmd, args, env) == -1)
			exit_error();
	}
	else
		not_found_error(*args, data);
	close_fd(tube[1]);
	free(cmd);
	free(args);
	// may have to free more stuffs of args here
}
/* donc d'abord faudrait voir pour voir genre les entrées avant l'exécution et apres les sorties apres le execve */