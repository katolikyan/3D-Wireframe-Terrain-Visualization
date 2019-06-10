/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 10:52:16 by tkatolik          #+#    #+#             */
/*   Updated: 2019/05/15 23:26:52 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void			*ft_memalloc(size_t size)
{
	void		*ptr;

	if (!(ptr = (void *)malloc(size)))
		return (NULL);
	ft_memset(ptr, 0, size);
	return (ptr);
}
