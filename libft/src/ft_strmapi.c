/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:57:10 by tkatolik          #+#    #+#             */
/*   Updated: 2019/05/15 23:27:13 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*new;
	unsigned int	i;

	i = 0;
	if (!s || !f)
		return (NULL);
	if (!(new = ft_memalloc(ft_strlen((char *)s) + 1)))
		return (NULL);
	while (((char *)s)[i])
	{
		new[i] = f(i, ((char *)s)[i]);
		i++;
	}
	new[i] = '\0';
	return (new);
}
