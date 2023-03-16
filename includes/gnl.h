/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ethaaalpha <ethaaalpha@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 12:39:23 by ebillon           #+#    #+#             */
/*   Updated: 2023/03/16 15:30:42 by ethaaalpha       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H

# include "../libft/libft.h"

# define BUFFER_SIZE 1

char			*get_next_line(int fd);
char			*read_the_line(char *buffer, int *end_file, int fd);
char			*next_line(char *buffer, int *end_file, int *i, int fd);
void			clean_buf(char *buffer, int *end_file);
char			*first_read(char *buffer, int *i);
unsigned int	next_line_len(char *buffer);
void			*ft_memmove(void *dst, const void *src, size_t len);
char			*gnl_strjoin(char *s1, char *s2);
size_t			gnl_strlen(const char *str);

#endif