/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 21:44:03 by tkatolik          #+#    #+#             */
/*   Updated: 2019/06/11 00:24:56 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** PROJECT:
** We are trying to find where would be the model coordinates in our
** window coordinate system. for that we use coordinate transformations
** (liniar algebra) and also multiply every coordinate to scale.
** If you multiply transofrmation matrix to coordinates of a point you
** will get new coordinates which describes position of the vector after
** transformation.
**
**  axis Y:
**	x' = x * cos(a) + z * sin(a)
**	y' = y
**	z' = -x * sin(a) + z * cos(a)
**
**  axis X;
**	x' = x;
**	y' = y * cos(a) + z * sin(a)
**	z' = -y * sin(a) + z * cos(a)
**
**  axis Z;
**	x' = x * cos(a) - y * sin(a)
**	y' = x * sin(a) + y * cos(a)
**	z' = z
**
**	To switch center cooditates from [0, 0] to the center of the figure:
**	x = x - map_x / 2  and  y = y - map_y / 2
**
**	To move figure to the center of view:
**	x' = windore_res_width / 2
**	y' = windore_res_high / 2
*/

t_line			project(t_glob *prms, int d_x, int d_y)
{
	t_line		new;
	t_prjct		xy;
	t_xy		dxy;

	dxy.x = d_x;
	dxy.y = d_y;
	new.out = 1;
	new.c0 = (int)MAP_Z[Y][X];
	new.c1 = (int)MAP_Z[Y + dxy.y][X + dxy.x];
	xy.c_x = (float)X - (float)prms->map_x / 2.0 + 0.5;
	xy.c_y = (float)Y - (float)prms->map_y / 2.0 + 0.5;
	project_z(prms, &new, &xy, &dxy);
	project_y(prms, &new, &xy, &dxy);
	project_x(prms, &new, &xy, &dxy);
	transforms_shift_optimization(prms, &new);
	return (new);
}

void			project_z(t_glob *prms, t_line *new, t_prjct *xy, t_xy *dxy)
{
	new->x0 = ((float)xy->c_x * cos(AZ) - (float)xy->c_y * sin(AZ)) * (float)SC;
	new->y0 = ((float)xy->c_x * sin(AZ) + (float)xy->c_y * cos(AZ)) * (float)SC;
	new->x1 = ((float)(xy->c_x + dxy->x) * cos(AZ) -
			(float)(xy->c_y + dxy->y) * sin(AZ)) * (float)SC;
	new->y1 = ((float)(xy->c_x + dxy->x) * sin(AZ) +
			(float)(xy->c_y + dxy->y) * cos(AZ)) * (float)SC;
	new->z0 = (float)MAP_Z_ADJ[Y][X];
	new->z1 = (float)MAP_Z_ADJ[Y + dxy->y][X + dxy->x];
	xy->tmp0 = new->x0;
	xy->tmp1 = new->x1;
}

void			project_y(t_glob *prms, t_line *new, t_prjct *xy, t_xy *dxy)
{
	new->x0 = (float)new->x0 * cos(AY) +
		(float)(MAP_Z_ADJ[Y][X] * SC) * sin(AY);
	new->x1 = (float)new->x1 * cos(AY) +
		(float)(MAP_Z_ADJ[Y + dxy->y][X + dxy->x] * SC) * sin(AY);
	MAP_Z_NEW[Y][X] = -xy->tmp0 * sin(AY) +
		(float)(MAP_Z_ADJ[Y][X] * SC) * cos(AY);
	MAP_Z_NEW[Y + dxy->y][X + dxy->x] = -xy->tmp1 * sin(AY) +
		(float)(MAP_Z_ADJ[Y + dxy->y][X + dxy->x] * SC) * cos(AY);
	xy->tmp0 = new->y0;
	xy->tmp1 = new->y1;
}

void			project_x(t_glob *prms, t_line *new, t_prjct *xy, t_xy *dxy)
{
	new->y0 = (float)new->y0 * cos(AX) + (float)(MAP_Z_NEW[Y][X]) * sin(AX);
	new->y1 = (float)new->y1 * cos(AX) +
		(float)(MAP_Z_NEW[Y + dxy->y][X + dxy->x]) * sin(AX);
	MAP_Z_NEW[Y][X] = (float)-xy->tmp0 * sin(AX) + (MAP_Z_NEW[Y][X]) * cos(AX);
	MAP_Z_NEW[Y + dxy->y][X + dxy->x] = (float)-xy->tmp1 * sin(AX) +
		(MAP_Z_NEW[Y + dxy->y][X + dxy->x]) * cos(AX);
	new->z0 = MAP_Z_NEW[Y][X];
	new->z1 = MAP_Z_NEW[Y + dxy->y][X + dxy->x];
}

void			transforms_shift_optimization(t_glob *prms, t_line *new)
{
	if (prms->trigger.distortion_1 == 1)
		distortion_1(prms, new);
	if (prms->trigger.distortion_2 == 1)
		distortion_2(prms, new);
	if (prms->trigger.distortion_3 == 1)
		distortion_3(prms, new);
	if (prms->trigger.perspective == 1)
		perspective(prms, new);
	new->x0 += RES_X / 2 + SHX;
	new->x1 += RES_X / 2 + SHX;
	new->y0 += RES_Y / 2 + SHY;
	new->y1 += RES_Y / 2 + SHY;
	if (((new->x0 > RES_X || new->x0 < 0) || (new->y0 > RES_Y || new->y0 < 0))
	&& ((new->x1 > RES_X || new->x1 < 0) || (new->y1 > RES_Y || new->y1 < 0)))
		new->out = 0;
}
