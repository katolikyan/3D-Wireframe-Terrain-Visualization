/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 13:07:32 by tkatolik          #+#    #+#             */
/*   Updated: 2019/06/10 17:51:26 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			redefine_colors(t_glob *prms)
{
	redefine_colors_background(prms);
	if (prms->trigger.depth == 1)
		calc_depth(prms);
	mlx_put_image_to_window(prms->mlx_ptr, prms->win_ptr,
			prms->img_data.img_ptr, 0, 0);
	if (B_C >= 0x808080 && BASE_C != DEF_BS_C_2)
	{
		BASE_C = DEF_BS_C_2;
		get_liniar_coefficients(prms);
		T_C = DEF_TXT_2;
	}
	if (B_C <= 0x808080 && BASE_C != DEF_BS_C)
	{
		BASE_C = DEF_BS_C;
		get_liniar_coefficients(prms);
		T_C = DEF_TXT_C;
	}
}

void			redefine_colors_background(t_glob *prms)
{
	int		i;

	i = 0;
	while (i < prms->img_data.l_s * RES_Y)
	{
		IMG[i + 3] = (unsigned char)BACK_A;
		IMG[i + 2] = (unsigned char)(B_C >> 16);
		IMG[i + 1] = (unsigned char)((B_C & 65280) >> 8);
		IMG[i + 0] = (unsigned char)(B_C & 255);
		i += 4;
	}
}

void			calc_depth(t_glob *prms)
{
	t_line		zero;

	Y = 0;
	while (Y < prms->map_y)
	{
		X = 0;
		while (X < prms->map_x)
		{
			if (X < prms->map_x - 1)
				zero = project(prms, 1, 0);
			if (Y < prms->map_y - 1)
				zero = project(prms, 0, 1);
			X += 1;
		}
		Y += 1;
	}
	prms->coeff_k.a =
		(ft_2d_double_array_min(MAP_Z_NEW, prms->map_y, prms->map_x) -
		ft_2d_double_array_max(MAP_Z_NEW, prms->map_y, prms->map_x)) / 255.0;
	prms->coeff_b.a =
		ft_2d_double_array_min(MAP_Z_NEW, prms->map_y, prms->map_x) -
		prms->coeff_k.a * 255.0;
}
