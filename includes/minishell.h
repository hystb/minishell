/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:39:36 by ebillon           #+#    #+#             */
/*   Updated: 2023/03/07 14:12:43 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* do some stuff there */
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <signal.h>

# define NEWLINE_ERROR "minishell: syntax error near \
unexpected token 'newline'\n"
# define PIPE_ERROR "minishell: syntax error near unexpected token '|'\n"
# define UNCOMP_ERROR "minishell: syntax error near unexpected token '"

typedef struct s_cmds
{
	int	nb_pipes;
	int	nb_sign;
	int	sp_quote_s;
	int	sp_quote_f;
	int	db_quote_s;
	int	db_quote_f;
}		t_cmds;

typedef struct s_env
{
	char			*name_var;
	char			*content_var;
	struct s_env	*next;
	struct s_env	*previous;
}					t_env;

typedef struct s_data
{
	t_env	**env_var;
	t_list	**cmd_lst;
}			t_data;

extern int	g_signal_handle;

t_list	**put_input_lst(char **input);
void	put_in_lst(char *input, t_list **cmd, t_cmds data_cmd);
void	split_map(char ***map_cmd, char *input, t_cmds data);
void	prepare_input(char *input, t_cmds *data_cmd);
void	make_map_pipe(char ***map_cmd, char **splited, int end, int start);
void	make_map(char ***map_cmd, char **splited, int end, int start);
int		last_pipe(char **splited, int i);
char	**ft_split_quote(char const *s, char c);
void	prepare_split(char *input);
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
t_env	**put_env(char **envp, t_data var_lst);
char	*is_env_vars(char *arg, t_data var_lst, int j);
void	jump_next_pipe(int *last_pipe, int *last_splited, char **splited);
char	*sub_env_var(char *var, char *arg, int start, t_data var_lst);
int		have_sign(char *str);
t_env	**make_env_in_lst(char **envp);
t_env	*envnew(char *content, int split);
void	env_add_back(t_env **lst, t_env *new);
void	make_node_env(char *env, int split, t_env **env_var);
void	free_env_var(t_env **env);
void	replace_env_var(t_data var_lst);
char	*find_env_var(char *var, t_data var_lst);
char	*input_error(char *in);
char	*sign_error(char *in, int space, int i);
char	*print_less_more_error(char *in, int i);
char	*many_sign(char *in);
void	print_undefine(char *s1, char *s2, char *s3, char c);
char	*print_less_error(char *in, int i, char *res);
void	replace_comment(char *in, int i);
char	*control_pipe(char *in, int i);
char	*replace_tab_and_printable(char *in);

#endif
