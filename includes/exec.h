/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:21:11 by ebillon           #+#    #+#             */
/*   Updated: 2023/01/30 13:16:39 by ebillon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/* about pipex */
# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include "../libft/libft.h"

typedef struct s_redirect
{
	int		fd;
	pid_t	pid;
}				t_redirect;

void	exit_error(void);
void	write_error(char *str);
void	not_found_error(char *cmd);
void	do_execute(char **args, char **env, int *tube);
void	do_heredoc(char *limiter);
void	do_child(int *tube, char **cmd, char **env);
char	*get_path(char *cmd, char **env);

/* redirections */
void	do_input(char *path);
void	do_commands(char **cmds, char **env);
void	fill_redirect(int fd, pid_t pid, t_redirect *data);

/* execution */
int		do_redirection(char **cmds);
void	pre_redirect(char **cmds, int argc, char **env, t_redirect *data);
void	redirect(char **cmds, int argc, char **env, t_redirect *data);
/* some stuff here */
#endif 