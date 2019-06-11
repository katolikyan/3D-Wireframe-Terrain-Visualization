/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstswap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 18:53:20 by tkatolik          #+#    #+#             */
/*   Updated: 2019/05/15 23:26:51 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void		ft_lstswapcon(t_list *lst1, t_list *lst2)
{
	void	*tmp_cont;
	size_t	tmp_size;

	if (!lst1 || !lst2)
		return ;
	tmp_cont = lst1->content;
	tmp_size = lst1->content_size;
	lst1->content = lst2->content;
	lst1->content_size = lst2->content_size;
	lst2->content = tmp_cont;
	lst2->content_size = tmp_size;
}
