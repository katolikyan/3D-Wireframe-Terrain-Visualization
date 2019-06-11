/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 21:28:29 by tkatolik          #+#    #+#             */
/*   Updated: 2019/05/15 23:12:53 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int			ft_atoi(const char *str)
{
	int		sum;
	int		sign;

	sign = 1;
	sum = 0;
	while (((*str == 32 || (*str <= 13 && *str >= 9)) && *str != 0))
		str++;
	if (*str == '-')
	{
		str++;
		sign = -1;
	}
	else if (*str == '+')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		sum = sum * 10 + (*str - 48);
		str++;
	}
	return (sum * sign);
}
