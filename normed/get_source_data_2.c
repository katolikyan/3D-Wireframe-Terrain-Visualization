/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_source_data_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:47:11 by tkatolik          #+#    #+#             */
/*   Updated: 2019/06/16 00:40:58 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

/*
** GET_MAP_Z
** creates an 2D array with stored hights inside.
*/

void			get_map_z(t_glob *prms)
{
	int			i;
	int			h;
	char		*line;
	char		**split;

	i = -1;
	h = 0;
	MAP_Z = ft_memalloc(sizeof(int *) * prms->map_y);
	while (++i < prms->map_y)
		MAP_Z[i] = ft_memalloc(sizeof(int) * prms->map_x);
	while (get_next_line(prms->fd, &line))
	{
		i = -1;
		split = ft_strsplit(line, ' ');
		while (++i < prms->map_x)
			MAP_Z[h][i] = ft_atoi(split[i]);
		h++;
		while (--i >= 0)
			free(split[i]);
		free(split);
		free(line);
	}
	free(line);
	get_map_z_extra(prms);
}

void			get_map_z_extra(t_glob *prms)
{
	int			i;
	int			h;

	i = -1;
	h = -1;
	MAP_Z_ADJ = ft_memalloc(sizeof(double *) * prms->map_y);
	MAP_Z_NEW = ft_memalloc(sizeof(double *) * prms->map_y);
	while (++i < prms->map_y)
	{
		MAP_Z_ADJ[i] = ft_memalloc(sizeof(double) * prms->map_x);
		MAP_Z_NEW[i] = ft_memalloc(sizeof(double) * prms->map_x);
	}
	while (++h < prms->map_y)
	{
		i = -1;
		while (++i < prms->map_x)
		{
			MAP_Z_ADJ[h][i] = (double)MAP_Z[h][i];
			MAP_Z_NEW[h][i] = MAP_Z_ADJ[h][i];
		}
	}
}
