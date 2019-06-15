/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:22:53 by tkatolik          #+#    #+#             */
/*   Updated: 2019/06/14 21:08:21 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			create_info(t_glob *prms)
{
	create_info_1_alpha_distortions(prms);
	create_info_2_scale_zoom(prms);
	create_info_3_focal_orto(prms);
	create_info_4_altitude_help(prms);
}

void			create_info_4_altitude_help(t_glob *prms)
{
	mlx_string_put(prms->mlx_ptr, prms->win_ptr,
		RES_X / 32, RES_Y / 4 + 34 * -1, T_C, "Altitude:");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr,
		RES_X / 32 + 30, RES_Y / 4 - 5, T_C, ft_itoa(prms->clr_h_max));
	mlx_string_put(prms->mlx_ptr, prms->win_ptr,
		RES_X / 32 + 30, RES_Y / 4 + 134, T_C, ft_itoa(prms->clr_h_min));
	altitude_info(prms);
	mlx_string_put(prms->mlx_ptr, prms->win_ptr,
		RES_X / 32, RES_Y - RES_Y / 16, T_C, "Press 'H' for help");
}

void			create_info_3_focal_orto(t_glob *prms)
{
	if (prms->trigger.perspective == 1)
	{
		mlx_string_put(prms->mlx_ptr, prms->win_ptr,
		RES_X / 32, RES_Y / 16 + 34 * 2, T_C, "Projection: persp");
		mlx_string_put(prms->mlx_ptr, prms->win_ptr,
		RES_X / 32, RES_Y / 16 + 34 * 3, T_C, "Focal lenght mm:  ~");
		mlx_string_put(prms->mlx_ptr, prms->win_ptr,
		RES_X / 32 + 196, RES_Y / 16 + 34 * 3, T_C, ft_itoa(FOCAL / 20));
	}
	else
	{
		mlx_string_put(prms->mlx_ptr, prms->win_ptr,
		RES_X / 32, RES_Y / 16 + 34 * 2, T_C, "Projection: ortho");
	}
}

void			create_info_2_scale_zoom(t_glob *prms)
{
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 32,
			RES_Y / 16 + 0, T_C, "Zoom multiplyer:");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 32 + 196,
			RES_Y / 16 + 0, T_C, ft_itoa(SC_MULT));
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 32,
			RES_Y / 16 + 34, T_C, "Altitude scale %:");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 32 + 196,
			RES_Y / 16 + 34, T_C,
			ft_itoa(ft_2d_double_array_max(MAP_Z_ADJ, prms->map_y, prms->map_x)
				* 100.0 / (double)prms->clr_h_max));
}

void			create_info_1_alpha_distortions(t_glob *prms)
{
	if (prms->trigger.distortion_1 == 1)
		mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X - 96,
			RES_Y / 16 + 0, T_C, "dist.1");
	if (prms->trigger.distortion_2 == 1)
		mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X - 96,
			RES_Y / 16 + 32, T_C, "dist.2");
	if (prms->trigger.distortion_3 == 1)
		mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X - 96,
			RES_Y / 16 + 64, T_C, "dist.3");
	if (BACK_A != 0)
	{
		mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X - 96,
			RES_Y / 16 + 128, T_C, "B");
		mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X - 64,
			RES_Y / 16 + 128, T_C, ft_itoa(BACK_A));
	}
	if (PIX_A != 0)
	{
		mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X - 96,
			RES_Y / 16 + 160, T_C, "P");
		mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X - 64,
			RES_Y / 16 + 160, T_C, ft_itoa(PIX_A));
	}
}
