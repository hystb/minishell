/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:39:36 by ebillon           #+#    #+#             */
/*   Updated: 2023/02/20 15:29:28 by ebillon          ###   ########.fr       */
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

typedef struct s_cmds
{
	int	nb_pipes;
	int	nb_sign;
	int	sp_quote_s;
	int	sp_quote_f;
	int	db_quote_s;
	int	db_quote_f;
}		t_cmds;

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
char	*make_input(char *promp_name);
void	config_signal(void);
void	handle_signal(int sig);
void	config_terminal(void);

#endif
