/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 13:58:53 by tkatolik          #+#    #+#             */
/*   Updated: 2019/05/15 23:27:16 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static size_t	ft_len(char const *s)
{
	size_t		n;
	size_t		wcnt;

	wcnt = ft_strwrdc(s);
	n = 0;
	while ((*s == ' ' || *s == '\n' || *s == '\t') && *s != 0)
		s++;
	while (wcnt > 0)
	{
		while ((*s == ' ' || *s == '\n' || *s == '\t') && *s != 0)
		{
			s++;
			n++;
		}
		while (*s != ' ' && *s != '\n' && *s != '\t' && *s != 0)
		{
			s++;
			n++;
		}
		wcnt--;
	}
	return (n);
}

char			*ft_strtrim(char const *s)
{
	char		*cpy;
	char		*crnt;
	size_t		len;

	if (!s)
		return (0);
	len = ft_len(s);
	if (!(cpy = ft_memalloc(len + 1)))
		return (0);
	crnt = cpy;
	while ((*s == ' ' || *s == '\n' || *s == '\t') && *s != 0)
		s++;
	while (*s && len-- > 0)
		*(crnt++) = *((char *)(s++));
	*crnt = 0;
	return (cpy);
}
