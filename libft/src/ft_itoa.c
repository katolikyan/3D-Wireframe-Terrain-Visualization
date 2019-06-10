/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:24:21 by tkatolik          #+#    #+#             */
/*   Updated: 2019/05/15 23:24:08 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static unsigned int	ft_numsize(int n)
{
	unsigned int	i;

	i = 0;
	if (n < 0)
		i++;
	while (n > 9 || n < -9)
	{
		i++;
		n /= 10;
	}
	i++;
	return (i);
}

char				*ft_itoa(int n)
{
	char			*str;
	unsigned int	i;
	unsigned int	nb;

	i = ft_numsize(n);
	if (!(str = ft_memalloc(sizeof(char) * i + 1)))
		return (0);
	str[i + 1] = 0;
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	i--;
	nb = n;
	while (i > 0)
	{
		str[i--] = nb % 10 + '0';
		nb /= 10;
	}
	if (str[i] != '-')
		str[i] = nb + '0';
	return (str);
}
