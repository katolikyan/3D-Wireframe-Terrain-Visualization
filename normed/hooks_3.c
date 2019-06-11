/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:58:17 by tkatolik          #+#    #+#             */
/*   Updated: 2019/06/11 00:52:55 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				key_release(int key, void *prm)
{
	t_glob		*prms;

	prms = (t_glob *)prm;
	if (((key >= 123 && key <= 126) || key == 24 || key == 27) &&
		prms->trigger.m_blur == 1)
	{
		BACK_A = 0;
		redraw(prms);
		BACK_A = 200;
	}
	return (0);
}

int				mouse_press(int key, int x, int y, void *prm)
{
	t_glob		*prms;

	prms = (t_glob *)prm;
	if (key == 5)
		SC += SC_MULT;
	if (key == 4 && SC > SC_MULT)
		SC -= SC_MULT;
	if (key == 3)
	{
		prms->trigger.mouse_3_press = 1;
		prms->trigger.mouse_xy.x = x;
		prms->trigger.mouse_xy.y = y;
		mouse_move(x, y, prm);
	}
	if (key == 1)
	{
		prms->trigger.mouse_1_press = 1;
		prms->trigger.mouse_xy.x = x;
		prms->trigger.mouse_xy.y = y;
		mouse_move(x, y, prm);
	}
	redraw(prms);
	return (0);
}

int				mouse_move(int x, int y, void *prm)
{
	t_glob	*prms;

	prms = (t_glob *)prm;
	if (prms->trigger.mouse_3_press)
	{
		SHX = x - prms->trigger.mouse_xy.x + SHX;
		SHY = y - prms->trigger.mouse_xy.y + SHY;
		prms->trigger.mouse_xy.x = x;
		prms->trigger.mouse_xy.y = y;
		redraw(prms);
	}
	if (prms->trigger.mouse_1_press)
	{
		AZ = AZ + (float)(x - prms->trigger.mouse_xy.x) / 150.0;
		AX = AX + (float)(y - prms->trigger.mouse_xy.y) / 150.0;
		prms->trigger.mouse_xy.x = x;
		prms->trigger.mouse_xy.y = y;
		redraw(prms);
	}
	return (0);
}

int				mouse_release(int key, int x, int y, void *prm)
{
	t_glob	*prms;

	x = y ? 0 : 0;
	prms = (t_glob *)prm;
	if (key == 3)
	{
		prms->trigger.mouse_3_press = 0;
		if (prms->trigger.m_blur == 1)
		{
			BACK_A = 0;
			redraw(prms);
			BACK_A = 200;
		}
	}
	if (key == 1)
	{
		prms->trigger.mouse_1_press = 0;
		if (prms->trigger.m_blur == 1)
		{
			BACK_A = 0;
			redraw(prms);
			BACK_A = 200;
		}
	}
	return (0);
}

int				close_window(void *prm)
{
	int			i;
	t_glob		*prms;

	i = -1;
	prms = prm;
	mlx_destroy_window(prms->mlx_ptr, prms->win_ptr);
	free(prms->img_data.img_ptr);
	free(prms->img_data.img_addr);
	while (++i < prms->map_y)
	{
		free(MAP_Z[i]);
		free(MAP_Z_ADJ[i]);
		free(MAP_Z_NEW[i]);
	}
	free(MAP_Z);
	free(MAP_Z_ADJ);
	free(MAP_Z_NEW);
	free(prms);
	exit(0);
	return (0);
}
