/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 21:44:03 by tkatolik          #+#    #+#             */
/*   Updated: 2019/06/10 20:31:33 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	t_rgb_kb		rgb;
	t_xy			delta_i;

	delta_i.x = delta;
	delta_i.y = i;
	color_2(prms, xy, &rgb, delta_i);
	clr = ((int)rgb.r << 16) + ((int)rgb.g << 8) + rgb.b;
	if (prms->coeff_k.r == 0 && prms->coeff_k.g == 0 && prms->coeff_k.b == 0
		&& prms->coeff_b.r == 0 && prms->coeff_b.g == 0 && prms->coeff_b.b == 0)
		clr = DEF_BS_C;
	if (prms->trigger.depth == 1)
		clr += ((depth(prms, xy, delta, i)) << 24);
	else
		clr += ((int)PIX_A << 24);
	return (clr);
}

void				color_2(t_glob *prms, t_line xy, t_rgb_kb *rgb, t_xy d_i)
{
	if (xy.c0 > xy.c1)
	{
		rgb->r = (((float)xy.c0 - fabsf(((float)(xy.c1 - xy.c0) /
				(float)d_i.x) * d_i.y)) - prms->coeff_b.r) / prms->coeff_k.r;
		rgb->g = (((float)xy.c0 - fabsf(((float)(xy.c1 - xy.c0) /
				(float)d_i.x) * d_i.y)) - prms->coeff_b.g) / prms->coeff_k.g;
		rgb->b = (((float)xy.c0 - fabsf(((float)(xy.c1 - xy.c0) /
				(float)d_i.x) * d_i.y)) - prms->coeff_b.b) / prms->coeff_k.b;
	}
	else
	{
		rgb->r = (((float)xy.c0 + fabsf(((float)(xy.c1 - xy.c0) /
				(float)d_i.x) * d_i.y)) - prms->coeff_b.r) / prms->coeff_k.r;
		rgb->g = (((float)xy.c0 + fabsf(((float)(xy.c1 - xy.c0) /
				(float)d_i.x) * d_i.y)) - prms->coeff_b.g) / prms->coeff_k.g;
		rgb->b = (((float)xy.c0 + fabsf(((float)(xy.c1 - xy.c0) /
				(float)d_i.x) * d_i.y)) - prms->coeff_b.b) / prms->coeff_k.b;
	}
}

int					depth(t_glob *prms, t_line xy, int delta, int i)
{
	float			alpha;

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
