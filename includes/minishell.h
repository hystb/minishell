/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebillon <ebillon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 15:39:36 by ebillon           #+#    #+#             */
/*   Updated: 2023/01/17 16:51:04 by ebillon          ###   ########lyon.fr   */
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
    int nb_pipes;
    int sp_quote_s;
    int sp_quote_f;
    int db_quote_s;
    int db_quote_f;
}       t_cmds;


#endif