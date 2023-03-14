/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 13:21:11 by ebillon           #+#    #+#             */
/*   Updated: 2023/03/07 14:34:19 by ebillon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "minishell.h"

typedef	struct s_listpids
{
	pid_t				pid;
	struct	s_listpids	*next;
}				t_listpids;

/* error */
void	exit_error(void);
void	write_error(char *str);
void	not_found_error(char *cmd);

/* redirections */
void	make_redir_inside(t_list *cmd);
int		do_input(char *path);
int		do_writing_file(char *path, int mode);
int		do_heredoc(char *limiter, t_data data); //bcause it's returning a fd;
void	make_redir_inside_aux(t_list *cmd, int *fd_target, t_data data);

/* execution */
int		is_builtins(t_list	**cmds);
int		do_builtins(t_data data);
int		args_len(char **args);
void	set_value_env(char *key, char *value, t_data var_lst);
void	delete_item_env(t_env *env, char *key);
int		get_env_lenght(t_data data);
char	**get_env_from_lst(t_data data);
char	*get_item_env(t_data data, char *key);
char	*get_path(char *cmd, char **env);
void	make_pipe(t_data data, t_listpids **pids, int *fd_in);
void	do_exec(t_data var_lst);
char	*get_next_line(int fd);

/* some stuff here */
#endif 
