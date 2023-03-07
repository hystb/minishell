/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 14:23:03 by nmilan            #+#    #+#             */
/*   Updated: 2023/03/07 14:30:04 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	replace_quote(t_data var_lst)
{
	t_list	*tmp;
	int		i;
	char	*new_content;
	int		j;

	tmp = *var_lst.cmd_lst;
	j = 0;
	while (tmp)
	{
		i = 0;
		while (tmp->content != NULL && tmp->content[i])
		{
			new_content = is_quote(tmp->content[i], var_lst, j);
			if (new_content)
				tmp->content[i] = new_content;
			i++;
		}
		tmp = tmp->next;
	}
}
