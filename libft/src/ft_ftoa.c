/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 14:09:12 by tkatolik          #+#    #+#             */
/*   Updated: 2019/05/15 23:22:50 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static char			*ft_reverse(char *str);
static char			*ft_round(char *str, int i, uintmax_t n, long double num);

char				*ft_ftoa(long double num, int precision)
{
	char			*str;
	int				i;
	uintmax_t		n;

	i = 0;
	str = ft_memalloc(21 + precision);
	(num < 0 ? (((str[i++] = '-') && (num *= -1))) : 0);
	n = num;
	while (n > 10)
	{
		str[i++] = n % 10 + '0';
		n /= 10;
	}
	str[i++] = n + '0';
	ft_reverse(str);
	str[i++] = '.';
	while (precision-- > 0)
	{
		n = num;
		n *= 10;
		num = num * 10 - n;
		n = num;
		str[i++] = n + '0';
	}
	return (ft_round(str, i, n, num));
}

static char			*ft_round(char *str, int i, uintmax_t n, long double num)
{
	i--;
	n = num;
	n *= 10;
	num = num * 10 - n;
	n = num;
	if (n >= 5)
	{
		if (str[i] != '9')
			str[i] += 1;
		else
		{
			while (str[i] == '9')
				str[i--] = '0';
			str[i] += 1;
		}
	}
	return (str);
}

static char			*ft_reverse(char *str)
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
