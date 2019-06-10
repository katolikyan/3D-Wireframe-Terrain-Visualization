/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 20:42:00 by tkatolik          #+#    #+#             */
/*   Updated: 2019/05/15 23:27:16 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char			*ft_strnstr(const char *hay, const char *ndl, size_t len)
{
	size_t		ndl_len;

	ndl_len = ft_strlen(ndl);
	if (!*ndl || !ndl_len)
		return ((char *)hay);
	while (*hay && len >= ndl_len)
	{
		if (*hay == *ndl && !ft_memcmp(hay, ndl, ndl_len))
			return ((char *)hay);
		hay++;
		len--;
	}
	return (0);
}
