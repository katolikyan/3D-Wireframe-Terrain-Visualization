/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:58:17 by tkatolik          #+#    #+#             */
/*   Updated: 2019/06/11 00:52:30 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				key_press_4_background_clr_alpha(int key, t_glob *prms)
{
	if (key == 30 && B_C < 0xFFFFFF)
		B_C += 0x030303;
	if (key == 33 && B_C >= 0x030303)
		B_C -= 0x030303;
	if (key == 22 && BACK_A >= 5)
		BACK_A -= 5;
	if (key == 26 && BACK_A <= 250)
		BACK_A += 5;
	if (key == 21 && PIX_A >= 5)
		PIX_A -= 5;
	if (key == 23 && PIX_A <= 250)
		PIX_A += 5;
	return (0);
}

int				key_press_3_scale_rotation(int key, t_glob *prms)
{
	if (key == 24)
		SC += SC_MULT;
	if (key == 27 && SC > SC_MULT)
		SC -= SC_MULT;
	if (key == 7 && SC_MULT < 10)
		SC_MULT += 1;
	if (key == 6 && SC_MULT > 1)
		SC_MULT -= 1;
	if (key == 125)
		AX += 0.05;
	if (key == 126)
		AX -= 0.05;
	if (key == 124)
		AZ += 0.05;
	if (key == 123)
		AZ -= 0.05;
	return (0);
}

int				key_press_2_views(int key, t_glob *prms)
{
	if (key == 17)
	{
		AX = 0.0;
		AY = 0.0;
		AZ = 0.0;
	}
	if (key == 3)
	{
		AX = -1.57;
		AY = 0.0;
		AZ = 0.0;
	}
	if (key == 15)
	{
		AX = -1.57;
		AY = 0.0;
		AZ = 1.57;
	}
	return (0);
}

int				key_press_1_altitude(int key, t_glob *prms)
{
	int			a;
	int			b;

	a = -1;
	b = -1;
	if (key == 43)
	{
		while (++a < prms->map_y)
		{
			b = -1;
			while (++b < prms->map_x)
				MAP_Z_ADJ[a][b] /= 1.05;
		}
	}
	if (key == 47)
	{
		while (++a < prms->map_y)
		{
			b = -1;
			while (++b < prms->map_x)
				MAP_Z_ADJ[a][b] *= 1.05;
		}
	}
	return (0);
}

int				key_press_0_altitude_reset(int key, t_glob *prms)
{
	int		a;
	int		b;

	a = -1;
	b = -1;
	if (key == 44)
	{
		while (++a < prms->map_y)
		{
			b = -1;
			while (++b < prms->map_x)
				MAP_Z_ADJ[a][b] = MAP_Z[a][b];
		}
	}
	return (0);
}
