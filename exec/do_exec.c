/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:39:23 by ebillon           #+#    #+#             */
/*   Updated: 2023/02/22 13:42:14 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/exec.h"
	// void	pre_redirect(char **cmds, int argc, char **env, t_redirect *data)

void	read_result(int fd)
{
	char buff[2];

	if (fd > 0)
	{
		while (read(fd, buff, 1))
			write(1, buff, 1);
		close_fd(fd);
	}
}

int	get_forklen(t_list **lst_cmd)
{
	int		len;
	t_list	*temp;

	len = 0;
	temp = *lst_cmd;
	while (temp)
	{
		if (ft_strncmp(temp->content[0], "|", 1))
			len++;
		temp = temp->next;
	}
	return (len);
}

void	do_exec(t_list **lst_cmd, char **env)
{
	t_redirect	data;
	int			status;
	int			fork_len;
	int			i;

	fork_len = get_forklen(lst_cmd);
	data.fd = -1;
	data.tube_out = -1;
	data.pids = ft_calloc(fork_len + 1, sizeof(pid_t));
	// printf("voici la forklen %d\n", fork_len);
	if (!data.pids)
		exit(1); //gerer erreurs mallocs et tout la
	pre_redirect(*lst_cmd, ft_lstsize(*lst_cmd), env, &data);
	// waitpid(data.pid, &status, 0);
	i = 0;
	while (i <= fork_len)
	{
		waitpid(data.pids[i], &status, 0);
		i++;
	}
	read_result(data.fd);
	free(data.pids);
}

// void	do_commands(char **cmds, char **env)
// {
// 	// int			status;
// 	// t_redirect  data;

// 	(void) cmds;
// 	(void) env;
// 	data.fd = -1;
// 	// data.tube_out = -1;
// 	// pre_redirect(cmds, 3, env, &data);
// 	// printf("pid: %d | fd: %d \n", data.pid, data.fd);
// 	// waitpid(data.pid, &status, 0);

// }
