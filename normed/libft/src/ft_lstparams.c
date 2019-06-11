/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstparams.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 17:54:41 by tkatolik          #+#    #+#             */
/*   Updated: 2019/05/15 23:26:49 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_list			*ft_lstparams(int ac, char **av)
{
	t_list		*begin;
	t_list		*crnt;
	int			i;

	i = 1;
	if (ac < 2)
		return (0);
	crnt = ft_lstnew(av[i], ft_strlen(av[i]) + 1);
	begin = crnt;
	while (++i < ac)
	{
		crnt->next = ft_lstnew(av[i], ft_strlen(av[i] + 1));
		crnt = crnt->next;
	}
	return (begin);
}
