/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 21:44:03 by tkatolik          #+#    #+#             */
/*   Updated: 2019/06/10 15:23:54 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** CREATE_IMAGE:
** iterates every point of the map. 
** If there is point on the left (current x < map size x) or
** draw from current [x,y] to [x + 1, y];
** If there is a point on the buttom (current y < map size y)
** draw from current [x,y] to [x, y + 1];
** Before drawing we have to make a projection from model coordinates to
** our window coordinate system. look at PROJECT function.
*/

void				create_image(t_glob *prms)
{
	prms->crt.y = 0;
	while (prms->crt.y < prms->map_y)
	{
		prms->crt.x = 0;
		while (prms->crt.x < prms->map_x)
		{
			if (prms->crt.x < prms->map_x - 1)
				draw(prms, project(prms, 1, 0));
			if (prms->crt.y < prms->map_y - 1)
				draw(prms, project(prms, 0, 1));
			prms->crt.x += 1;
		}
		prms->crt.y += 1;
	}
}

/*
** DRAW:
** 1. we finding differences berween coordinates A and B.
** 2. we are looking for the biggest difference in absolut values,
** 	  because it will be the number of pixels we have to draw from A to B.
** 3. i = is index to iterate from 0 to our delta.
** 4. d = steps for each pixel on shorter side, kind of index for shorter side.
** 5. final coordinates if biggest delta is X:
**
**    x_final = x0 + copysign(i, delta.x);         
**			
**			copysign needed to understand in which way to draw, 
**			to the right or to the left. To the up or down
**			if we talking ablout y.
**
**	  y_final = y0 + copysign((round(d * delta.y)), delta.y)
** 
**			d = will always less then 1, so (d * delta.y) allows
**				to understand how high we are and 'round' allows
**				jump to next y coordinate when number has more
**				then 5 after dot.
*/

void				draw(t_glob *prms, t_line xy)
{	
	t_xy			delta;
	int				i;
	float			d;

	if (xy.out == 0)
		return ;	
	delta.x = xy.x1 - xy.x0;
	delta.y = xy.y1 - xy.y0;
	i = -1;
	if (abs(delta.x) >= abs(delta.y))
		while (++i < abs(delta.x))
		{
			d = (float)i / delta.x;
			put_in_image(prms, xy.x0 + copysign(i, delta.x),
					xy.y0 + copysign(round(d * delta.y), delta.y),
					color(prms, xy, delta.x, i));
		}
	else
		while (++i < abs(delta.y))
		{
			d = (float)i / delta.y;
			put_in_image(prms, xy.x0 + copysign(round(d * delta.x), delta.x),
					xy.y0 + copysign(i, delta.y),
					color(prms, xy, delta.y, i));
		}
}

/*
** PUT IN IMAGE:
** puts rgb fom 'c' to pixel of image in memory.
** First 'if' checks if the pixel we are looking for is out of the image;
** Send 'if' checks if that pixel filled with background color.
** If not - it's epty and we can p
*/

void				put_in_image(t_glob *prms, int x, int y, int c)
{
	if ( (y >= RES_Y) || (x * 4 > prms->img_data.l_s) || y < 0 || 
			x * 4 < 0)
		return ;
	(prms->img_data.img_addr)[y * prms->img_data.l_s + x * 4 + 3] = 
		(unsigned char)((c & 0xFF000000) >> 24);
	(prms->img_data.img_addr)[y * prms->img_data.l_s + x * 4 + 2] = 
		(unsigned char)((c & 0xFF0000) >> 16);
	(prms->img_data.img_addr)[y * prms->img_data.l_s + x * 4 + 1] = 
		(unsigned char)((c & 0xFF00) >> 8);
	(prms->img_data.img_addr)[y * prms->img_data.l_s + x * 4 + 0] =
	   	(unsigned char)(c & 0xFF);
}

/*
** COLOR:
** By using x = (y - b)/k we get colors for any pixel;
**
** How do we calculate high of a pixel:
** xy.c0 = is high of the start point.
** xy.c1 = is high of the end point.
**
**	  ^									  ^
**    |								   -- |			* 
** -- |						*		   d  |			
** |  |								   e  |
** dH |								   l  |
** |  |							       t  |
** -- |    *						   a  |		
**    |   							   -- |		*
**  ----------------------------->	   --------------------------->
**    |	   |------deta------|			  |		|---|dH
**											
**
**	delta = always the longest pass from point A to point B.
**			we will get it from "draw" function.
**	
**	y = c0 + ((c1 - c0) / delta) * i	   c1 - c0    = this is 'dH'.
**										   dH / delta = step of H for every
**														pixel of delta;
**										   ... * i    = i is pixel steps from
**														0 (point A) to B,
**														so 'max i = delta';
**										   c0 + ...   = H of first point + h
**														of current pixel.
*/

int					color(t_glob *prms, t_line xy, int delta, int i)
{
	int				clr;
	float			r;
	float			g;
	float			b;
	
	if (xy.c0 > xy.c1)
	{
		r = (((float)xy.c0 - fabsf(((float)(xy.c1 - xy.c0) / (float)delta) * i))
			- prms->coeff_b.r) / prms->coeff_k.r;
		g = (((float)xy.c0 - fabsf(((float)(xy.c1 - xy.c0) / (float)delta) * i))
			- prms->coeff_b.g) / prms->coeff_k.g;
		b = (((float)xy.c0 - fabsf(((float)(xy.c1 - xy.c0) / (float)delta) * i))
			- prms->coeff_b.b) / prms->coeff_k.b;
	}
	else
	{
		r = (((float)xy.c0 + fabsf(((float)(xy.c1 - xy.c0) / (float)delta) * i))
			- prms->coeff_b.r) / prms->coeff_k.r;
		g = (((float)xy.c0 + fabsf(((float)(xy.c1 - xy.c0) / (float)delta) * i))
			- prms->coeff_b.g) / prms->coeff_k.g;
		b = (((float)xy.c0 + fabsf(((float)(xy.c1 - xy.c0) / (float)delta) * i))
			- prms->coeff_b.b) / prms->coeff_k.b;
	}
	clr = ((int)r << 16) + ((int)g << 8) + b;

//	if the map is flat;
	if (prms->coeff_k.r == 0 && prms->coeff_k.g == 0 && prms->coeff_k.b == 0
		&& prms->coeff_b.r == 0 && prms->coeff_b.g == 0 && prms->coeff_b.b == 0)
		clr = DEF_BS_C;

	if (prms->trigger.depth == 1) 
		clr += ((depth(prms, xy, delta, i)) << 24);
	else
		clr += ((int)PIX_A << 24);
	return (clr);
}

int				depth(t_glob *prms, t_line xy, int delta, int i) 
{
	float		alpha;
	if (xy.z0 > xy.z1)
	{
		alpha = ((xy.z0 - fabs(((fabs(xy.z1) - fabs(xy.z0)) /
				(float)delta) * i)) - prms->coeff_b.a) / (prms->coeff_k.a);
	}
	else
	{
		alpha = ((xy.z0 + fabs(((fabs(xy.z1) - fabs(xy.z0)) /
				(float)delta) * i)) - prms->coeff_b.a) / (prms->coeff_k.a);
	}
	return (alpha);
}
