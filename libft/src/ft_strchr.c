/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 20:22:39 by tkatolik          #+#    #+#             */
/*   Updated: 2019/05/15 23:27:10 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char			*ft_strchr(const char *s, int c)
{
	char		a;
	char		*ptr;

	ptr = (char *)s;
	a = (char)c;
	while (*ptr)
	{
		if (*ptr == a)
			return (ptr);
		ptr++;
	}
	if (*ptr == a)
		return (ptr);
	return (NULL);
}
