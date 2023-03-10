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

# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include "../libft/libft.h"
# include "../includes/minishell.h"

int	pwd(void);
int	ft_export(char	*data, t_data var);
int	echo(char **args);
int	cd(t_data data, t_list *cmd);
#endif
