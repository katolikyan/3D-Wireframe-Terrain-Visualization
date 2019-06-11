/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 21:44:03 by tkatolik          #+#    #+#             */
/*   Updated: 2019/06/11 00:24:36 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			perspective(t_glob *prms, t_line *new)
{
	t_xy	old0;
	t_xy	old1;

	old0.x = new->x0;
	old0.y = new->y0;
	old1.x = new->x1;
	old1.y = new->y1;
	new->x0 = (double)FOCAL * (double)new->x0 / (float)((float)FOCAL - new->z0);
	new->y0 = (double)FOCAL * (double)new->y0 / (float)((float)FOCAL - new->z0);
	new->x1 = (double)FOCAL * (double)new->x1 / (float)((float)FOCAL - new->z1);
	new->y1 = (double)FOCAL * (double)new->y1 / (float)((float)FOCAL - new->z1);
	if ((old0.x > 0 && new->x0 < 0) || (old0.x < 0 && new->x0 > 0) ||
	(old0.y > 0 && new->y0 < 0) || (old0.y < 0 && new->y0 > 0) ||
	(old1.x > 0 && new->x1 < 0) || (old1.x < 0 && new->x1 > 0) ||
	(old1.y > 0 && new->y1 < 0) || (old1.y < 0 && new->y1 > 0))
	{
		new->x0 = 0;
		new->y0 = 0;
		new->x1 = 0;
		new->y1 = 0;
	}
}

void			distortion_1(t_glob *prms, t_line *new)
{
	double		max;

	max = ft_2d_double_array_max(MAP_Z_NEW, prms->map_y, prms->map_x);
	if (new->z0 != 0)
	{
		new->x0 = fabs((new->x0 * new->x0 / ((max + 100) - new->z0)));
		new->y0 = fabs((new->y0 * new->y0 / ((max + 100) - new->z0)));
	}
	if (new->z1 != 0)
	{
		new->x1 = fabs((new->x1 * new->x1 / ((max + 100) - new->z1)));
		new->y1 = fabs((new->y1 * new->y1 / ((max + 100) - new->z1)));
	}
}

void			distortion_2(t_glob *prms, t_line *new)
{
	double		max;

	max = ft_2d_double_array_max(MAP_Z_NEW, prms->map_y, prms->map_x);
	if (new->z0 != 0)
	{
		new->x0 = copysign((new->x0 * new->x0 / ((max + 100) - new->z0)),
				new->x0);
		new->y0 = copysign((new->y0 * new->y0 / ((max + 100) - new->z0)),
				new->y0);
	}
	if (new->z1 != 0)
	{
		new->x1 = copysign((new->x1 * new->x1 / ((max + 100) - new->z1)),
				new->x1);
		new->y1 = copysign((new->y1 * new->y1 / ((max + 100) - new->z1)),
				new->y1);
	}
}

void			distortion_3(t_glob *prms, t_line *new)
{
	double		max;

	max = ft_2d_double_array_max(MAP_Z_NEW, prms->map_y, prms->map_x);
	if (new->z0 != 0)
	{
		new->x0 = (new->x0 / -new->z0) * (1 / tan(0.05));
		new->y0 = (new->y0 / -new->z0) * (1 / tan(0.05));
	}
	if (new->z1 != 0)
	{
		new->x1 = (new->x1 / -new->z1) * (1 / tan(0.05));
		new->y1 = (new->y1 / -new->z1) * (1 / tan(0.05));
	}
}
