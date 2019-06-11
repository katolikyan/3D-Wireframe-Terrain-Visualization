/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/18 14:09:12 by tkatolik          #+#    #+#             */
/*   Updated: 2019/05/15 23:23:12 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static void			ft_round(char *str, int i, uintmax_t n, long double num);
static void			ft_append(char *str, int i, int e);
static void			ft_seek(long double *num, int *e);

char				*ft_ftoe(long double num, int precision)
{
	char			*str;
	int				i;
	int				e;
	uintmax_t		n;

	i = 0;
	e = 0;
	str = ft_memalloc(21 + precision);
	(num < 0 ? (((str[i++] = '-') && (num *= -1))) : 0);
	ft_seek(&num, &e);
	str[i++] = num + '0';
	str[i++] = '.';
	while (precision-- > 0)
	{
		n = num;
		n *= 10;
		num = num * 10 - n;
		n = num;
		str[i++] = n + '0';
	}
	ft_round(str, i, n, num);
	ft_append(str, i, e);
	return (str);
}

static void			ft_seek(long double *num, int *e)
{
	while (*num < 1)
	{
		*e -= 1;
		*num *= 10;
	}
	while (*num > 10)
	{
		*e += 1;
		*num /= 10;
	}
	return ;
}

static void			ft_append(char *str, int i, int e)
{
	str[i++] = 'e';
	if (e < 0)
	{
		str[i++] = '-';
		e *= -1;
	}
	else
		str[i++] = '+';
	str[i++] = e / 10 + '0';
	str[i++] = e % 10 + '0';
	return ;
}

static void			ft_round(char *str, int i, uintmax_t n, long double num)
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
	return ;
}
