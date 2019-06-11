/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 17:10:12 by tkatolik          #+#    #+#             */
/*   Updated: 2019/05/15 23:26:51 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t			ft_lstsize(t_list *begin_list)
{
	size_t		i;

	i = 0;
	if (!begin_list)
		return (0);
	while (begin_list)
	{
		i++;
		begin_list = begin_list->next;
	}
	return (i);
}
