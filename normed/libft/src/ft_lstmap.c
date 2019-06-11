/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 19:35:16 by tkatolik          #+#    #+#             */
/*   Updated: 2019/05/15 23:26:29 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*new;

	if (!lst || !f || !(new = ft_memalloc(sizeof(t_list))))
		return (0);
	new = f(lst);
	new->next = ft_lstmap(lst->next, f);
	return (new);
}
