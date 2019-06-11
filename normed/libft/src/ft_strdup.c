/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 17:07:43 by tkatolik          #+#    #+#             */
/*   Updated: 2019/05/15 23:27:10 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char		*ft_strdup(const char *s1)
{
	char	*new;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s1);
	new = (char *)malloc(sizeof(char) * len + 1);
	if (!new)
		return (NULL);
	while (i < len)
	{
		new[i] = s1[i];
		i++;
	}
	new[i] = 0;
	return (new);
}
