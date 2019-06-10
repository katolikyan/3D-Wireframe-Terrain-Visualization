/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 20:22:39 by tkatolik          #+#    #+#             */
/*   Updated: 2019/05/15 23:27:16 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char			*ft_strrchr(const char *s, int c)
{
	char		a;
	char		*ptr;
	char		*last;

	last = NULL;
	ptr = (char *)s;
	a = (char)c;
	while (*ptr)
	{
		if (*ptr == a)
			last = ptr;
		ptr++;
	}
	if (*ptr == a)
		return (ptr);
	return (last);
}
