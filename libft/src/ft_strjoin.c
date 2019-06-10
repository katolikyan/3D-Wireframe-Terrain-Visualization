/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 13:36:19 by tkatolik          #+#    #+#             */
/*   Updated: 2019/05/15 23:27:13 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;

	if (!s1 || !s2)
		return (0);
	if (!(new = ft_memalloc((ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (0);
	new = ft_strcat(new, s1);
	new = ft_strcat(new, s2);
	return (new);
}
