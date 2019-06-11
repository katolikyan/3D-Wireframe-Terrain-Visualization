/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 23:00:53 by tkatolik          #+#    #+#             */
/*   Updated: 2019/05/15 23:22:24 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int		ft_atoi_base16(const char *str, int str_base)
{
	int			sum;

	sum = 0;
	while ((*str >= '0' && *str <= '9')
				|| (*str >= 'a' && *str <= ((str_base - 11) + 'a')) ||
					(*str >= 'A' && *str <= ((str_base - 11) + 'A')))
	{
		if (*str >= '0' && *str <= '9')
			sum = sum * str_base + (*str++ - '0');
		else if (*str >= 'a' && *str <= 'f')
			sum = sum * str_base + (*str++ - 'a' + 10);
		else if (*str >= 'A' && *str <= 'F')
			sum = sum * str_base + (*str++ - 'A' + 10);
	}
	return (sum);
}

int				ft_atoi_base(const char *str, int str_base)
{
	int			sum;
	int			sign;

	if (!str || str_base > 16 || str_base < 2)
		return (0);
	sum = 0;
	sign = 1;
	while (*str <= 32 && *str != 0)
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	if (str_base <= 10)
	{
		while (*str >= '0' && *str <= ((str_base - 1) + 48))
			sum = sum * str_base + (*str++ - '0');
	}
	else
		return (sign * ft_atoi_base16(str, str_base));
	return (sign * sum);
}
