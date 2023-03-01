/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:21:11 by ebillon           #+#    #+#             */
/*   Updated: 2023/02/22 13:40:05 by ebillon          ###   ########.fr       */
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

typedef	struct s_listpids
{
	pid_t				pid;
	struct	s_listpids	*next;
}				t_listpids;

typedef struct s_redirect
{
	int	*tube;
	int	out;
	int	in;
}				t_redirect;

void	exit_error(void);
void	write_error(char *str);
void	not_found_error(char *cmd);
void	do_execute(char **args, char **env, int *tube, t_redirect *data);
void	do_heredoc(char *limiter);
void	close_fd(int fd);
char	*get_path(char *cmd, char **env);

/* redirections */
int		do_redir_in(char **cmds, t_redirect *data);
int 	do_redir_out(char **cmds, t_redirect *data);
int		do_input(char *path);
void	do_commands(char **cmds, char **env);
int		do_writing_file(char *path, int mode);
void	fill_redirect(int fd, int *i, t_redirect *data);
void	echo(char **args);

/* execution */
int		do_redirection(t_list *cmds, t_redirect *data);
void	pre_redirect(t_list *cmds, int argc, char **env, t_redirect *data);
void	redirect(t_list *cmds, int argc, char **env, t_redirect *data);
void	do_exec(t_list **lst_cmd, char **env);

void	read_result(int fd);
void	make_pipe(t_list **cmds, char **env, t_listpids **list, int *fd_in);
/* some stuff here */
#endif 