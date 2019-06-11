/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treenew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 19:25:09 by tkatolik          #+#    #+#             */
/*   Updated: 2019/05/15 23:27:19 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_btree			*ft_treenew(const void *content, size_t content_size)
{
	t_btree		*node;

	if (!(node = (t_btree *)malloc(sizeof(t_btree))))
		return (0);
	node->right = 0;
	node->left = 0;
	if (!content)
	{
		node->content = 0;
		node->content_size = 0;
	}
	else
	{
		if (!(node->content = ft_memalloc(content_size)))
			return (0);
		node->content = ft_memcpy(node->content, content, content_size);
		node->content_size = content_size;
	}
	return (node);
}
