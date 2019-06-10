/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/19 20:34:05 by tkatolik          #+#    #+#             */
/*   Updated: 2019/05/15 23:27:14 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char		*ft_strndup(const char *s1, size_t len)
{
	char	*new;
	size_t	i;

	i = 0;
	if (!(new = (char *)ft_memalloc(len + 1)))
		return (NULL);
	while (i < len && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = 0;
	return (new);
}
