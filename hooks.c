/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:58:17 by tkatolik          #+#    #+#             */
/*   Updated: 2019/06/10 15:46:01 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_press_1_altitude(int key, t_glob *prms);
static int	key_press_2_views(int key, t_glob *prms);
static int	key_press_3_scale_rotation(int key, t_glob *prms);
static int	key_press_4_background_clr_alpha(int key, t_glob *prms);
static int	key_press_5_transformations(int key, t_glob *prms);
static int	key_press_6_help_info(int key, t_glob *prms);
static int	key_press_7_depth_focal_motion_blur(int key, t_glob *prms);
static int	key_press_8_reset_close(int key, t_glob *prms);

int			key_press(int key, void *prm)
{
	t_glob		*prms;

	prms = (t_glob *)prm;

//	reset params & close program;
	key_press_8_reset_close(key, prms);
//	depth, focal lenght & motion blur;
	key_press_7_depth_focal_motion_blur(key, prms);
//	Help & info;	
	key_press_6_help_info(key, prms);
//	Transformations;
	key_press_5_transformations(key, prms);
//	Background color, alpha & pix alpha;
	key_press_4_background_clr_alpha(key, prms);
//	scale & rotation;
	key_press_3_scale_rotation(key, prms);
//	view;
	key_press_2_views(key, prms);
//	change altitude;
	key_press_1_altitude(key, prms);

	redraw(prms);
	return (0);
}

int			key_press_8_reset_close(int key, t_glob *prms)
{
//	close programm
	if (key == 53)
		close_window(prms);

//	reset params;
	if (key == 29)
	{
		SC = DEF_SC;
		AX = DEF_AX;
		AY = DEF_AY;
		AZ = DEF_AZ;
		SHX = DEF_SHX;
		SHY = DEF_SHY;
	}
	
	return (0);
}

int			key_press_7_depth_focal_motion_blur(int key, t_glob *prms)
{
//	motion_blur
	if (key == 46 && prms->trigger.m_blur == 0)
	{
			prms->trigger.m_blur = 1;
			BACK_A = 200;
	}
	else if (key == 46 && prms->trigger.m_blur == 1)
	{
			prms->trigger.m_blur = 0;
			BACK_A = 0;
   	}

//	depth
	if (key == 2 && prms->trigger.depth == 0)
			prms->trigger.depth = 1;
	else if (key == 2 && prms->trigger.depth == 1)
			prms->trigger.depth = 0;

//	focal_lenght change;
	if (key == 28 && FOCAL > 300)
		FOCAL -= 100;
	if (key == 25 && FOCAL < 10000)
		FOCAL += 100;

	return (0);
}

int			key_press_6_help_info(int key, t_glob *prms)
{
	// info
	if (key == 34 && prms->trigger.info == 0)
			prms->trigger.info = 1;
	else if (key == 34 && prms->trigger.info == 1)
			prms->trigger.info = 0;

	// help
	if (key == 4 && prms->trigger.help == 0)
			prms->trigger.help = 1;
	else if (key == 4 && prms->trigger.help == 1)
			prms->trigger.help = 0;

	return (0);
}

int			key_press_5_transformations(int key, t_glob *prms)
{
//	perspective
	if (key == 35 && prms->trigger.perspective == 0)
			prms->trigger.perspective = 1;
	else if (key == 35 && prms->trigger.perspective == 1)
			prms->trigger.perspective = 0;

//	distortion_1
	if (key == 18 && prms->trigger.distortion_1 == 0)
			prms->trigger.distortion_1 = 1;
	else if (key == 18 && prms->trigger.distortion_1 == 1)
			prms->trigger.distortion_1 = 0;

//	distortion_2
	if (key == 19 && prms->trigger.distortion_2 == 0)
			prms->trigger.distortion_2 = 1;
	else if (key == 19 && prms->trigger.distortion_2 == 1)
			prms->trigger.distortion_2 = 0;

//	distortion_3
	if (key == 20 && prms->trigger.distortion_3 == 0)
			prms->trigger.distortion_3 = 1;
	else if (key == 20 && prms->trigger.distortion_3 == 1)
			prms->trigger.distortion_3 = 0;

	return (0);
}

int			key_press_4_background_clr_alpha(int key, t_glob *prms)
{
//	Background colors;
	if (key == 30 && B_C < 0xFFFFFF)
		B_C += 0x030303;
	if (key == 33 && B_C >= 0x030303)
		B_C -= 0x030303;

//	Back alpha change;
	if (key == 22 && BACK_A >= 5)
		BACK_A -= 5;
	if (key == 26 && BACK_A <= 250)
		BACK_A += 5;

//	Pixel alpha change;
	if (key == 21 && PIX_A >= 5)
		PIX_A -= 5;
	if (key == 23 && PIX_A <= 250)
		PIX_A += 5;

	return (0);
}

int			key_press_3_scale_rotation(int key, t_glob *prms)
{	
//	scale;
	if (key == 24)
			SC += SC_MULT;
	if (key == 27 && SC > SC_MULT)
			SC -= SC_MULT;
	if (key == 7 && SC_MULT < 10)
			SC_MULT += 1;
	if (key == 6 && SC_MULT > 1)
			SC_MULT -= 1;

//	rotation;
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

int			key_press_2_views(int key, t_glob *prms)
{
//	top
	if (key == 17)
	{
		AX = 0.0;
		AY = 0.0;
		AZ = 0.0;
	}
//	front
	if (key == 3)
	{
		AX = -1.57;
		AY = 0.0;
		AZ = 0.0;
	}
//	right
	if (key == 15)
	{
		AX = -1.57;
		AY = 0.0;
		AZ = 1.57;
	}

	return (0);
}

int			key_press_1_altitude(int key, t_glob *prms)
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
			while(++b < prms->map_x)	
				MAP_Z_ADJ[a][b] /= 1.05;
		}
	}
	if (key == 47)
	{
		while (++a < prms->map_y)
		{
			b = -1;
			while(++b < prms->map_x)	
				MAP_Z_ADJ[a][b] *= 1.05;
		}
	}

//	reset altitude;
	if (key == 44)
	{
		while (++a < prms->map_y)
		{
			b = -1;
			while(++b < prms->map_x)	
				MAP_Z_ADJ[a][b] = MAP_Z[a][b];
		}
	}

	return (0);
}

int			key_release(int key, void *prm)
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

int 		mouse_press(int key, int x, int y, void *prm)
{
	t_glob		*prms;

	prms = (t_glob *)prm; 
//	scale
	if (key == 5)
			SC += SC_MULT;
	if (key == 4 && SC > SC_MULT)
			SC -= SC_MULT;

//	shift
	if (key == 3)
	{
		prms->trigger.mouse_3_press = 1;
		prms->trigger.mouse_xy.x = x;
		prms->trigger.mouse_xy.y = y;
		mouse_move(x, y, prm);
	}

//	rotate
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

int			mouse_move(int x, int y, void *prm)
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

int			mouse_release(int key, int x, int y, void *prm)
{
	t_glob	*prms;
	
	x += 0;
	y += 0;
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

int			close_window(void *prm)
{
	t_glob	*prms;
	
	prms = prm;
	mlx_destroy_window(prms->mlx_ptr, prms->win_ptr);
	free(prms->img_data.img_ptr);
	free(prms->img_data.img_addr);
	for (int i = 0; i < prms->map_y; i++)
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
