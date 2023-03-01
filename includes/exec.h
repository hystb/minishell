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

/* error */
void	exit_error(void);
void	write_error(char *str);
void	not_found_error(char *cmd);

/* redirections */
void	make_redir_inside(t_list *cmd, char **env);
int		do_input(char *path);
int		do_writing_file(char *path, int mode);
void	do_heredoc(char *limiter);

/* execution */
char	*get_path(char *cmd, char **env);
void	make_pipe(t_list **cmds, char **env, t_listpids **pids, int *fd_in);
void	do_exec(t_list **lst_cmd, char **env);

/* some stuff here */
#endif 