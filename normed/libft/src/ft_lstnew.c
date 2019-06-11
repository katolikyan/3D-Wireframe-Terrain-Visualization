/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 18:48:44 by tkatolik          #+#    #+#             */
/*   Updated: 2019/05/15 23:26:31 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_list			*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*node;

	if (!(node = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	node->next = 0;
	if (!content)
	{
		node->content = 0;
		node->content_size = 0;
	}
	else
	{
		if (!(node->content = ft_memalloc(content_size)))
			return (NULL);
		node->content = ft_memcpy(node->content, content, content_size);
		node->content_size = content_size;
	}
	return (node);
}
