/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:39:36 by ebillon           #+#    #+#             */
/*   Updated: 2023/04/03 15:17:35 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>

# define NEWLINE_ERROR "minishell: syntax error near \
unexpected token 'newline'\n"
# define PIPE_ERROR "minishell: syntax error near unexpected token '|'\n"
# define UNCOMP_ERROR "minishell: syntax error near unexpected token '"
# define ERROR_QUOTE "minishell: not close quote\n"
# define SHLVL_ERROR "minishell: warning: shell level too high, resetting to 1\n"

typedef struct s_cmds
{
	int	nb_pipes;
	int	nb_sign;
	int	sp_quote_s;
	int	sp_quote_f;
	int	db_quote_s;
	int	db_quote_f;
}		t_cmds;

typedef struct s_listpids
{
	pid_t				pid;
	struct s_listpids	*next;
}				t_listpids;

typedef struct s_env
{
	char			*name_var;
	char			*content_var;
	struct s_env	*next;
	struct s_env	*previous;
}					t_env;

typedef struct s_data
{
	t_env		**env_var;
	t_list		**cmd_lst;
	t_listpids	**lst_pids;
}			t_data;

extern int	g_signal_handle;

/* parsing */
t_list	**put_input_lst(char **input);
void	put_in_lst(char *input, t_list **cmd, t_cmds data_cmd);
void	split_map(char ***map_cmd, char *input);
void	prepare_input(char *input, t_cmds *data_cmd);
void	make_map_pipe(char ***map_cmd, char **splited, int end, int start);
void	make_map(char ***map_cmd, char **splited, int end, int start);
int		last_pipe(char **splited, int i);
char	**ft_split_quote(char const *s, char c);
void	prepare_split(char **input, char c, int i, int index);
void	change_space(char *str, int end, int start, int type);
void	change_split(char **splited);
int		ft_tablen(char ***map);
char	*add_space_pipe(char *input);
int		need_space(char *input);
char	*realloc_input(char *input, int i);
char	*add_pipe(char *input, int i);
int		need_pipe(char *input);
char	*add_pipe_sign(char *input);
void	del_free_content(void **content);
char	*make_input(char *promp_name, t_data var_lst);
void	config_signal(void);
void	handle_signal(int sig);
char	is_quote_in_sign(char c, char in);
t_env	**put_env(char **envp, t_data var_lst);
char	*is_env_vars(char *arg, t_data var_lst, int j, int i);
void	jump_next_pipe(int *last_pipe, int *last_splited, char **splited);
char	*sub_env_var(char *var, char *arg, int start, t_data var_lst);
int		have_sign(char *str);
t_env	**make_env_in_lst(char **envp);
t_env	*envnew(char *content, int split);
void	env_add_back(t_env **lst, t_env *new);
void	make_node_env(char *env, int split, t_env **env_var);
void	free_env_var(t_env **env);
void	replace_env_var(t_data var_lst);
char	*find_env_var(char *var, t_data var_lst, int i);
char	*input_error(char *in, t_data var_lst);
char	*sign_error(char *in, int space, int i, char c);
char	*print_less_more_error(char *in, int i);
char	*many_sign(char *in, int count_less, int count_more, int c);
void	print_undefine(char *s1, char *s2, char *s3, char c);
char	*print_less_error(char *in, int i, char *res);
char	*control_pipe(char *in, int i);
char	*replace_tab_and_printable(char *in);
void	replace_quote(t_data var_lst);
int		end_env(int start, char *arg);
void	replace_pipe_in_quote(char ***map);
char	*is_quote(char *in, int i, char c);
void	change_quote(char *in);
void	restore_quote(t_data var_lst);
char	*get_var(char *arg, t_data var_lst, int j, int i);
void	is_env_synthax(char *in, int j, int *i);
char	*empty_before_pipe(char *in, int i, int is_content);
char	*space_sign(char *input, int i);
char	**split_negativ(char **content, int i, int j, int k);
void	split_env(t_data var_lst);
int		is_space(char *in);
int		tab_size(char **str);
char	**free_env_case(char **a, char **b, char **res, int j);

/* builtins */
int		pwd(void);
int		ft_export(t_data data, char **args);
void	ft_exit(t_data data, int duplicate[2]);
int		echo(char **args);
int		cd(t_data data, t_list *cmd);
int		do_export_nargs(t_data data);
int		env(t_data data);
int		unset(t_data data, char **vars);
void	free_tab(char **tab);

/* error */
void	exit_error(t_data data);
void	write_error(char *str, t_data data);
void	not_found_error(char *cmd, t_data data);
void	free_data(t_data data);
void	free_pids(t_listpids **pids);
int		quit_redir(int a, int b);
int		quit_simple(t_data data, int ret_exit);

/* redirections */
int		make_redir_inside(t_list *cmd, int i);
int		do_input(char *path);
int		do_writing_file(char *path, int mode);
int		do_heredoc(char *limiter, t_data data);
char	*rechange_target(char *str);
char	*realloc_sp_sign(char *input, char c, int i);
char	*realloc_db_sign(char *input, char c, int i);
void	make_redir_inside_aux(t_list *cmd, int *fd_target, t_data data);

/* env lst */
void	set_value_env(char *key, char *value, t_data var_lst);
void	delete_item_env(t_env *env, char *key);
int		get_env_lenght(t_data data);
char	**get_env_from_lst(t_data data, int i);
char	*get_item_env(t_data data, char *key);

/* execution */
void	change_negative(char **tab);
int		is_builtins(t_list	**cmds);
int		is_blank(char *str);
void	add_pids(pid_t value, t_listpids **list, t_data data);
int		do_builtins(t_data data, int duplicate[2]);
int		do_parent_builtins(t_data data);
int		args_len(char **args);
char	*get_path(char *cmd, char **env, t_data data);
int		make_only(t_data data, t_listpids **pids, int *fd_in);
void	make_pipe(t_data data, t_listpids **pids, int *fd_in);
void	restore_counter(int *a, int *b);
char	*get_next_line(int fd);
void	do_exec(t_data var_lst, t_list **lst_cmd, int fd_old, t_list *tmp);
int		ft_strcmp(char *a, char *b);
#endif
