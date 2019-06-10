/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:19:15 by tkatolik          #+#    #+#             */
/*   Updated: 2019/05/15 23:27:16 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static size_t		wordcnt(char const *str, char a)
{
	size_t			i;

	i = 0;
	while (*str)
	{
		while (*str == a && *str != 0)
			str++;
		while (*str != a && *str != 0)
			str++;
		if (*str != 0)
			i++;
		else if (*(str - 1) != a)
			i++;
	}
	return (i);
}

static char			**ft_fillarr(char **arr, char const *s, char c)
{
	unsigned int	a;
	unsigned int	b;

	a = 0;
	b = 0;
	while (*s)
	{
		while (*s == c && *s != 0)
			s++;
		while (*s != c && *s != 0)
			arr[a][b++] = *(s++);
		if (*s == 0 && *(s - 1) == c)
		{
			arr[a] = 0;
			return (arr);
		}
		arr[a][b] = 0;
		b = 0;
		a++;
	}
	arr[a] = 0;
	return (arr);
}

char				**ft_strsplit(char const *s, char c)
{
	char			**arr;
	size_t			wrd;
	size_t			len;
	unsigned int	i;

	if (!s)
		return (0);
	i = 0;
	len = ft_strlen(s);
	wrd = wordcnt(s, c);
	if (!(arr = (char **)malloc(sizeof(char *) * wrd + 1)))
		return (0);
	while (i < wrd)
	{
		if (!(arr[i] = (char *)malloc(len + 1)))
			return (0);
		i++;
	}
	return (arr = ft_fillarr(arr, s, c));
}
