/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:39:36 by ebillon           #+#    #+#             */
/*   Updated: 2023/01/23 13:57:13 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* do some stuff there */
# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmds
{
	int	nb_pipes;
	int	sp_quote_s;
	int	sp_quote_f;
	int	db_quote_s;
	int	db_quote_f;
}		t_cmds;

t_list	**put_input_lst(char *input);
void	put_in_lst(char *input, t_list **cmd, t_cmds data_cmd);
void	split_map(char ***map_cmd, char *input, t_cmds data);
void	prepare_input(char *input, t_cmds *data_cmd);
void	make_map_pipe(char ***map_cmd, char **splited, int end, int start);
void	make_map(char ***map_cmd, char **splited, int end, int start);

#endif
