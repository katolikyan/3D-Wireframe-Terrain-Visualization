/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_source_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:47:11 by tkatolik          #+#    #+#             */
/*   Updated: 2019/06/16 00:29:22 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
#include <limits.h>
#include <float.h>

/*
**	This block collects and stores data from the provided file.
*/

void			get_source_data(t_glob *prms, char *source)
{
	if ((prms->fd = open(source, O_RDONLY)) < 0)
	{
		write(1, "Error: Open file failed\n", 25);
		exit(0) ;
	}
	get_map_xy(prms);
	close(prms->fd);
	if ((prms->fd = open(source, O_RDONLY)) < 0)
	{
		write(1, "Error: Open file failed\n", 25);
		exit(0) ;
	}
	get_map_z(prms);
	get_liniar_coefficients(prms);
	close(prms->fd);
}

/*
** GET_LINIAR_COEFFICIENTS:
** When we have 'max high' and 'min high', and we know their RGB code, we are
** able to build liniar dependens for every chenel;
**
** General liniar dependens is: y = kx + b;			x = color; y = high;
**
** 	 ^    \	  /R
** 	 |     \ /				We do 3 different dependenses for every chanel;
** 	 |      / 				We are finding K and B coefficients here;
** 	 |...../.\......G		After that, when we know high for any pixel,
** 	 |    /   \				we just put high on Y position and find X for every
** --|---/-----\----->		chanel: x = (y - b)/k
**   |			B
**	Example of liniar 		after calculating equasion system we will get:
**	dependenses.			k = (min_y - max_y) / (min_x - max_x)
**							b = min_y - k * min_x  ||  b = max_y - k * max_x
*/

void			get_liniar_coefficients(t_glob *prms)
{
	prms->clr_h_max = ft_2d_int_array_max(MAP_Z, prms->map_y, prms->map_x);
	prms->clr_h_min = ft_2d_int_array_min(MAP_Z, prms->map_y, prms->map_x);
	prms->clr_min.r = (BASE_C >> 16);
	prms->clr_min.g = ((BASE_C & 0xFF00) >> 8);
	prms->clr_min.b = (BASE_C & 0xFF);
	prms->clr_max.r = (TOP_C >> 16); 
	prms->clr_max.g = ((TOP_C & 0xFF00) >> 8);
	prms->clr_max.b = (TOP_C & 0xFF);
	prms->coeff_k.r = ((float)prms->clr_h_min - (float)prms->clr_h_max) /
	   				((float)prms->clr_min.r - (float)prms->clr_max.r);
	prms->coeff_k.g = ((float)prms->clr_h_min - (float)prms->clr_h_max) /
	   				((float)prms->clr_min.g - (float)prms->clr_max.g);
	prms->coeff_k.b = ((float)prms->clr_h_min - (float)prms->clr_h_max) /
	   				((float)prms->clr_min.b - (float)prms->clr_max.b);
	prms->coeff_b.r = ((float)prms->clr_h_min - 
		prms->coeff_k.r * (float)prms->clr_min.r);
	prms->coeff_b.g = (float)prms->clr_h_min -
	   	prms->coeff_k.g * (float)prms->clr_min.g;
	prms->coeff_b.b = (float)prms->clr_h_min - 
		prms->coeff_k.b * (float)prms->clr_min.b;
}	

void			get_map_xy(t_glob *prms)
{
	int			i;
	char		*line_start;
	char		*line;
	
	i = 0;
	while (get_next_line(prms->fd, &line))
	{
		line_start = line;
		if (i++ == 0)
		{
			while (*line)
			{
				if (*line == ' ' || *line == '\t')
					line++;
				else
				{
					while (*line != ' ' && *line != '\t' && *line != '\0')
						line++;
					prms->map_x += 1;
				}	
			}
		}
		else if (i != 0)
			check_map(prms, line_start);
		prms->map_y += 1;
		if (line_start)
			free(line_start);
	}
	free(line);
	return ;
}

void			check_map(t_glob *prms, char *line)
{
	int		check;

	check = 0;
	while (*line)
	{
		if (*line == ' ' || *line == '\t')
			line++;
		else
		{
			while (*line != ' ' && *line != '\0')
				line++;
			check += 1;
		}	
	}
	if (check != prms->map_x)
	{
		write(1, "Error: invalid map\n", 19);
		exit (0);
	}
}

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
	// allocate ADJ array;
	i = -1;
	h = -1;
	MAP_Z_ADJ = ft_memalloc(sizeof(double *) * prms->map_y);
	while (++i < prms->map_y)
		MAP_Z_ADJ[i] = ft_memalloc(sizeof(double) * prms->map_x);
	while (++h < prms->map_y)
	{
		i = -1;
		while (++i < prms->map_x)
			MAP_Z_ADJ[h][i] = (double)MAP_Z[h][i];
	}

	// allocate NEW Z array;
	i = -1;
	h = -1;
	MAP_Z_NEW = ft_memalloc(sizeof(double *) * prms->map_y);
	while (++i < prms->map_y)
		MAP_Z_NEW[i] = ft_memalloc(sizeof(double) * prms->map_x);
	while (++h < prms->map_y)
	{
		i = -1;
		while (++i < prms->map_x)
			MAP_Z_NEW[h][i] = MAP_Z_ADJ[h][i];
	}
	return ;
}
