/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:58:17 by tkatolik          #+#    #+#             */
/*   Updated: 2019/06/11 00:51:57 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				key_press(int key, void *prm)
{
	t_glob		*prms;

	prms = (t_glob *)prm;
	key_press_8_reset_close(key, prms);
	key_press_7_depth_focal_motion_blur(key, prms);
	key_press_6_help_info(key, prms);
	key_press_5_transformations(key, prms);
	key_press_4_background_clr_alpha(key, prms);
	key_press_3_scale_rotation(key, prms);
	key_press_2_views(key, prms);
	key_press_1_altitude(key, prms);
	key_press_0_altitude_reset(key, prms);
	redraw(prms);
	return (0);
}

int				key_press_8_reset_close(int key, t_glob *prms)
{
	if (key == 53)
		close_window(prms);
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

int				key_press_7_depth_focal_motion_blur(int key, t_glob *prms)
{
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
	if (key == 2 && prms->trigger.depth == 0)
		prms->trigger.depth = 1;
	else if (key == 2 && prms->trigger.depth == 1)
		prms->trigger.depth = 0;
	if (key == 28 && FOCAL > 300)
		FOCAL -= 100;
	if (key == 25 && FOCAL < 10000)
		FOCAL += 100;
	return (0);
}

int				key_press_6_help_info(int key, t_glob *prms)
{
	if (key == 34 && prms->trigger.info == 0)
		prms->trigger.info = 1;
	else if (key == 34 && prms->trigger.info == 1)
		prms->trigger.info = 0;
	if (key == 4 && prms->trigger.help == 0)
		prms->trigger.help = 1;
	else if (key == 4 && prms->trigger.help == 1)
		prms->trigger.help = 0;
	return (0);
}

int				key_press_5_transformations(int key, t_glob *prms)
{
	if (key == 35 && prms->trigger.perspective == 0)
		prms->trigger.perspective = 1;
	else if (key == 35 && prms->trigger.perspective == 1)
		prms->trigger.perspective = 0;
	if (key == 18 && prms->trigger.distortion_1 == 0)
		prms->trigger.distortion_1 = 1;
	else if (key == 18 && prms->trigger.distortion_1 == 1)
		prms->trigger.distortion_1 = 0;
	if (key == 19 && prms->trigger.distortion_2 == 0)
		prms->trigger.distortion_2 = 1;
	else if (key == 19 && prms->trigger.distortion_2 == 1)
		prms->trigger.distortion_2 = 0;
	if (key == 20 && prms->trigger.distortion_3 == 0)
		prms->trigger.distortion_3 = 1;
	else if (key == 20 && prms->trigger.distortion_3 == 1)
		prms->trigger.distortion_3 = 0;
	return (0);
}
