/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strwrdc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:04:19 by tkatolik          #+#    #+#             */
/*   Updated: 2019/05/15 23:27:16 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t				ft_strwrdc(char const *str)
{
	size_t			i;

	i = 0;
	if (!str)
		return (0);
	while (*str)
	{
		while (*str == ' ' || *str == '\t' || *str == '\n')
			str++;
		while (*str != ' ' && *str != '\t' && *str != '\n' && *str != '\0')
			str++;
		if (*str != 0)
			i++;
		else if (*(str - 1) != ' ' && *(str - 1) != '\t' && *(str - 1) != '\n')
			i++;
	}
	return (i);
}
