/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:22:53 by tkatolik          #+#    #+#             */
/*   Updated: 2019/06/10 16:12:30 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		create_info_1_alpha_distortions(t_glob *prms);
static void		create_info_2_scale_zoom(t_glob *prms);
static void		create_info_3_focal_orto(t_glob *prms);
static void		create_info_4_altitude_help(t_glob *prms);

void			create_info(t_glob *prms)
{

//	distortion & alpha;
	create_info_1_alpha_distortions(prms);
//	scale and zoom;	
	create_info_2_scale_zoom(prms);
//	focal / orto;
	create_info_3_focal_orto(prms);
//	altitude and help;
	create_info_4_altitude_help(prms);
}

void			create_info_4_altitude_help(t_glob *prms)
{
// 	altitude;
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, 
		RES_X / 32, RES_Y / 4 + 34 * -1, T_C, "Altitude:");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, 
		RES_X / 32 + 30, RES_Y / 4 - 5, T_C, ft_itoa(prms->clr_h_max));
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, 
		RES_X / 32 + 30, RES_Y / 4 + 134, T_C, ft_itoa(prms->clr_h_min));
	altitude_info(prms);

//	help;
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
		RES_X / 32, RES_Y / 16 + 34 * 2, T_C, "Projection: ortho" );
	}
}

void			create_info_2_scale_zoom(t_glob *prms)
{
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 32,
			RES_Y / 16 + 0, T_C, "Zoom multiplyer:");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 32 + 196,
			RES_Y / 16 + 0, T_C, ft_itoa(SC_MULT));

	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 32,
			RES_Y / 16 + 34, T_C, "Altitude scale:");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 32 + 196,
			RES_Y / 16 + 34, T_C, 
			ft_itoa(ft_2d_double_array_max(MAP_Z_ADJ, prms->map_y, prms->map_x)
					 * 100.0 / (double)prms->clr_h_max));
}

void			create_info_1_alpha_distortions(t_glob *prms)
{
//	distoritions;
	if (prms->trigger.distortion_1 == 1)
		mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X - 96, 
			RES_Y / 16 + 0, T_C, "dist.1");
	if (prms->trigger.distortion_2 == 1)
		mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X - 96, 
			RES_Y / 16 + 32, T_C, "dist.2");
	if (prms->trigger.distortion_3 == 1)
		mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X - 96, 
			RES_Y / 16 + 64, T_C, "dist.3");

//	alpha info;
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

void			altitude_info(t_glob *prms)
{
	t_line		xy;
	int			delta;	
	int			i;
	int			width;
	
	width = 10;
	xy.x0 = RES_X / 32;
	xy.y0 = RES_Y / 4;
	xy.x1 = RES_X / 32;
	xy.y1 = RES_Y / 4 + 100;
	xy.c1 = prms->clr_h_min;
	xy.c0 = prms->clr_h_max;
	delta = 150;

	while (width-- > 0)
	{
		i = -1;
		while (++i < delta)
			mlx_pixel_put(prms->mlx_ptr, prms->win_ptr, 
					xy.x0, xy.y0 + i, color(prms, xy, delta, i));
		xy.x0 += 1;
	}
}

void			create_help(t_glob *prms)
{
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 2 - 200,
	RES_Y / 3 + 34 * -6, T_C, "WELCOME TO FDF (WIREFRAME MAP GENERATOR)");

//	left column;
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 4, // 2 - 49
	RES_Y / 3 + 34 * -4, T_C, "HOTKEYS:");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 4,
	RES_Y / 3 + 34 * -3, T_C, "i       - hide or show info.");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 4,
	RES_Y / 3 + 34 * -2, T_C, "arrows  - rotate.");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 4,
	RES_Y / 3 + 34 * -1, T_C, "r  t  f - right, top, front projection.");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 4,
	RES_Y / 3 + 34 * 0, T_C, "p       - perspective projection.");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 4,
	RES_Y / 3 + 34 * 1, T_C, "d       - depth of field effect.");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 4,
	RES_Y / 3 + 34 * 2, T_C, "z  x    - decrease/increase zoom multiplier.");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 4,
	RES_Y / 3 + 34 * 3, T_C, "<  >    - change altitude scale.");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 4,
	RES_Y / 3 + 34 * 4, T_C, "[  ]    - change background color.");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 4,
	RES_Y / 3 + 34 * 5, T_C, "m       - motion blur activation.");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 4,
	RES_Y / 3 + 34 * 8, T_C, "MOUSE KEYS:");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 4,
	RES_Y / 3 + 34 * 9, T_C, "Hold left click to rotate.");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 4,
	RES_Y / 3 + 34 * 10, T_C, "Hold scroll for panorama.");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 4,
	RES_Y / 3 + 34 * 11, T_C, "Scroll for zoom in - zoom out.");

//	right column;
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 2 + 160,
	RES_Y / 3 + 34 * -3, T_C, "1       - distortion 1.");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 2 + 160,
	RES_Y / 3 + 34 * -2, T_C, "2       - distortion 2.");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 2 + 160,
	RES_Y / 3 + 34 * -1, T_C, "3       - distortion 3.");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 2 + 160,
	RES_Y / 3 + 34 * 0, T_C, "4, 5    - image alpha decrease/increase.");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 2 + 160,
	RES_Y / 3 + 34 * 1, T_C, "6, 7    - background alpha decrease/increase.");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 2 + 160,
	RES_Y / 3 + 34 * 2, T_C, "8, 9    - decrease/increas focal lenght.");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 2 + 160,
	RES_Y / 3 + 34 * 3, T_C, "0       - reset zoom & rotation.");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 2 + 160,
	RES_Y / 3 + 34 * 4, T_C, "-  +    - zoom out, zoom in.");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 2 + 160,
	RES_Y / 3 + 34 * 5, T_C, "/       - reset altitude scale.");

// 	buttom links;
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 2 - 292,
	RES_Y / 3 + 34 * 16, T_C, "42-project by Tigran Katolikyan:  \
							   github.com/katolikyan");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 2 - 292,
	RES_Y / 3 + 34 * 17, T_C, "Special thanks to Stepan Nikitin: \
   								github.com/nikitinste");
}
