/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 13:41:05 by nmilan            #+#    #+#             */
/*   Updated: 2023/02/20 14:55:32 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include "minishell.h"

int		pwd(void);
int		ft_export(t_data data, char **args);
void	ft_exit(t_data data);
int		echo(char **args);
int		cd(t_data data, t_list *cmd);
int		do_export_nargs(t_data data);
int		env(t_data data);
int		unset(t_data data, char **vars);
#endif
