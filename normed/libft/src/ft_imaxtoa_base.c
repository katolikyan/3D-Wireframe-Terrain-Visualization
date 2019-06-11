/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_imaxtoa_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/15 16:24:03 by tkatolik          #+#    #+#             */
/*   Updated: 2019/05/15 23:23:21 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static char			*ft_reverse(char *str);

char				*ft_imaxtoa_base(intmax_t num, uintmax_t base, int flag)
{
	char			*str;
	int				i;
	uintmax_t		n;

	i = 0;
	str = ft_memalloc(21);
	(num < 0 ? ((str[i++] = '-') && (num *= -1)) : 0);
	n = num;
	while (n > (base - 1))
		if (n % base < 10)
		{
			str[i++] = n % base + '0';
			n /= base;
		}
		else
		{
			str[i++] = (flag == 1 ? n % base + 'A' - 10 : n % base + 'a' - 10);
			n /= base;
		}
	if (n < 10)
		str[i] = n + '0';
	else
		str[i] = (flag == 1 ? n + 'A' - 10 : n + 'a' - 10);
	return (ft_reverse(str));
}

char				*ft_reverse(char *str)
{
	int				i;
	int				len;

	i = 0;
	len = ft_strlen(str);
	if (str[i] == '-')
		i++;
	while (i < --len)
	{
		str[i] = str[i] ^ str[len];
		str[len] = str[i] ^ str[len];
		str[i] = str[i] ^ str[len];
		i++;
	}
	return (str);
}
