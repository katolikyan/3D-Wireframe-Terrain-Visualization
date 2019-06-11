/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 21:44:03 by tkatolik          #+#    #+#             */
/*   Updated: 2019/06/10 20:32:03 by tkatolik         ###   ########.fr       */
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
	if ((y >= RES_Y) || (x * 4 > prms->img_data.l_s) || y < 0 ||
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
