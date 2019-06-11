/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 18:49:19 by tkatolik          #+#    #+#             */
/*   Updated: 2019/05/15 23:27:13 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	room;
	size_t	ofset;
	size_t	ldst;
	size_t	lsrc;

	ldst = ft_strlen(dst);
	lsrc = ft_strlen(src);
	room = dstsize - (ldst + 1);
	ofset = 0;
	if (dstsize <= ldst + 1)
		return (lsrc + dstsize);
	else
	{
		while (room-- > 0 && *src)
		{
			dst[ldst + ofset] = src[ofset];
			ofset++;
		}
		dst[ldst + ofset] = '\0';
	}
	return (ldst + lsrc);
}
