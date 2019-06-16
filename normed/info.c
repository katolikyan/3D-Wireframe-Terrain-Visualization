/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:22:53 by tkatolik          #+#    #+#             */
/*   Updated: 2019/06/16 01:04:59 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			create_info(t_glob *prms)
{
	create_info_0_distortions(prms);
	create_info_1_alpha(prms);
	create_info_2_scale_zoom(prms);
	create_info_3_focal_orto(prms);
	create_info_4_altitude_help(prms);
}

void			create_info_4_altitude_help(t_glob *prms)
{
	char		*h_max;
	char		*h_min;

	h_max = ft_itoa(prms->clr_h_max);
	h_min = ft_itoa(prms->clr_h_min);
	mlx_string_put(prms->mlx_ptr, prms->win_ptr,
		RES_X / 32, RES_Y / 4 + 34 * -1, T_C, "Altitude:");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr,
		RES_X / 32 + 30, RES_Y / 4 - 5, T_C, h_max);
	mlx_string_put(prms->mlx_ptr, prms->win_ptr,
		RES_X / 32 + 30, RES_Y / 4 + 134, T_C, h_min);
	altitude_info(prms);
	mlx_string_put(prms->mlx_ptr, prms->win_ptr,
		RES_X / 32, RES_Y - RES_Y / 16, T_C, "Press 'H' for help");
	free(h_max);
	free(h_min);
}

void			create_info_3_focal_orto(t_glob *prms)
{
	char		*focal;

	focal = ft_itoa(FOCAL / 20);
	if (prms->trigger.perspective == 1)
	{
		mlx_string_put(prms->mlx_ptr, prms->win_ptr,
		RES_X / 32, RES_Y / 16 + 34 * 2, T_C, "Projection: persp");
		mlx_string_put(prms->mlx_ptr, prms->win_ptr,
		RES_X / 32, RES_Y / 16 + 34 * 3, T_C, "Focal lenght mm:  ~");
		mlx_string_put(prms->mlx_ptr, prms->win_ptr,
		RES_X / 32 + 196, RES_Y / 16 + 34 * 3, T_C, focal);
	}
	else
	{
		mlx_string_put(prms->mlx_ptr, prms->win_ptr,
		RES_X / 32, RES_Y / 16 + 34 * 2, T_C, "Projection: ortho");
	}
	free(focal);
}

void			create_info_2_scale_zoom(t_glob *prms)
{
	char		*sc_mult;
	char		*sc_alti;

	sc_mult = ft_itoa(SC_MULT);
	sc_alti =
		ft_itoa(ft_2d_double_array_max(MAP_Z_ADJ, prms->map_y, prms->map_x)
				* 100.0 / (double)prms->clr_h_max);
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 32,
			RES_Y / 16 + 0, T_C, "Zoom multiplyer:");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 32 + 196,
			RES_Y / 16 + 0, T_C, sc_mult);
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 32,
			RES_Y / 16 + 34, T_C, "Altitude scale %:");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 32 + 196,
			RES_Y / 16 + 34, T_C, sc_alti);
	free(sc_mult);
	free(sc_alti);
}

void			create_info_1_alpha(t_glob *prms)
{
	char		*alpha_b;
	char		*alpha_p;

	alpha_b = ft_itoa(BACK_A);
	alpha_p = ft_itoa(PIX_A);
	if (BACK_A != 0)
	{
		mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X - 96,
			RES_Y / 16 + 128, T_C, "B");
		mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X - 64,
			RES_Y / 16 + 128, T_C, alpha_b);
	}
	if (PIX_A != 0)
	{
		mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X - 96,
			RES_Y / 16 + 160, T_C, "P");
		mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X - 64,
			RES_Y / 16 + 160, T_C, alpha_p);
	}
	free(alpha_b);
	free(alpha_p);
}
