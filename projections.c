/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 21:44:03 by tkatolik          #+#    #+#             */
/*   Updated: 2019/06/10 15:23:31 by tkatolik         ###   ########.fr       */
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

t_line				project(t_glob *prms, int d_x, int d_y)
{
	t_line			new;
	float		c_x;
	float		c_y;
	float		temp0;
	float		temp1;

	new.out = 1;
	new.c0 = (int)MAP_Z[Y][X];
	new.c1 = (int)MAP_Z[Y + d_y][X + d_x];
	c_x = (float)X - (float)prms->map_x / 2.0 + 0.5;
	c_y = (float)Y - (float)prms->map_y / 2.0 + 0.5;

//	transformations axis Z;
	new.x0 = ((float)c_x * cos(AZ) - (float)c_y * sin(AZ)) * (float)SC;
	new.y0 = ((float)c_x * sin(AZ) + (float)c_y * cos(AZ)) * (float)SC;
	new.x1 = ((float)(c_x + d_x) * cos(AZ) -
			(float)(c_y + d_y) * sin(AZ)) * (float)SC;
	new.y1 = ((float)(c_x + d_x) * sin(AZ) +
		   	(float)(c_y + d_y) * cos(AZ)) * (float)SC;
	new.z0 = (float)MAP_Z_ADJ[Y][X];							
	new.z1 = (float)MAP_Z_ADJ[Y + d_y][X + d_x];				
	temp0 = new.x0;
	temp1 = new.x1;												
	
//	transformations axis Y;
	new.x0 = (float)new.x0 * cos(AY) + (float)(MAP_Z_ADJ[Y][X] * SC) * sin(AY);
	new.x1 = (float)new.x1 * cos(AY) +
		     (float)(MAP_Z_ADJ[Y + d_y][X + d_x] * SC) * sin(AY);
	MAP_Z_NEW[Y][X] = -temp0 * sin(AY) +
	   	(float)(MAP_Z_ADJ[Y][X] * SC) * cos(AY);
	MAP_Z_NEW[Y + d_y][X + d_x] = -temp1 * sin(AY) +
	   	(float)(MAP_Z_ADJ[Y + d_y][X + d_x] * SC) * cos(AY);
	temp0 = new.y0;												
	temp1 = new.y1;

//	transformations axis X;
	new.y0 = (float)new.y0 * cos(AX) + (float)(MAP_Z_NEW[Y][X]) * sin(AX);
	new.y1 = (float)new.y1 * cos(AX) +
		   	 (float)(MAP_Z_NEW[Y + d_y][X + d_x]) * sin(AX);
	MAP_Z_NEW[Y][X] = (float)-temp0 * sin(AX) + (MAP_Z_NEW[Y][X]) * cos(AX);
	MAP_Z_NEW[Y + d_y][X + d_x] = (float)-temp1 * sin(AX) +
	   	(MAP_Z_NEW[Y + d_y][X + d_x]) * cos(AX);
	new.z0 = MAP_Z_NEW[Y][X];
	new.z1 = MAP_Z_NEW[Y + d_y][X + d_x];						

//	check for extra transformations;
	if (prms->trigger.distortion_1 == 1)
		distortion_1(prms, &new);
	if (prms->trigger.distortion_2 == 1)
		distortion_2(prms, &new);
	if (prms->trigger.distortion_3 == 1)
		distortion_3(prms, &new);
	if (prms->trigger.perspective == 1)
		perspective(prms, &new);

//	x y coordinate shift;
	new.x0 += RES_X / 2 + SHX;
	new.x1 += RES_X / 2 + SHX;
	new.y0 += RES_Y / 2 + SHY;
	new.y1 += RES_Y / 2 + SHY;

//	optimization (don't draw if both points are out of the map);
	if (((new.x0 > RES_X || new.x0 < 0) || (new.y0 > RES_Y || new.y0 < 0))
		&& ((new.x1 > RES_X || new.x1 < 0) || (new.y1 > RES_Y || new.y1 < 0)))
		new.out = 0;
	
	return (new);
}

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

//	protection from int overflow;
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
