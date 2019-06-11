/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/31 16:22:53 by tkatolik          #+#    #+#             */
/*   Updated: 2019/06/11 01:07:32 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 4,
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
	create_help_2(prms);
	create_help_3(prms);
}

void			create_help_2(t_glob *prms)
{
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
}

void			create_help_3(t_glob *prms)
{
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 2 + 160,
	RES_Y / 3 + 34 * 2, T_C, "8, 9    - decrease/increas focal lenght.");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 2 + 160,
	RES_Y / 3 + 34 * 3, T_C, "0       - reset zoom & rotation.");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 2 + 160,
	RES_Y / 3 + 34 * 4, T_C, "-  +    - zoom out, zoom in.");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 2 + 160,
	RES_Y / 3 + 34 * 5, T_C, "/       - reset altitude scale.");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 2 - 292,
	RES_Y / 3 + 34 * 16, T_C, "42-project by Tigran Katolikyan:  \
	github.com/katolikyan");
	mlx_string_put(prms->mlx_ptr, prms->win_ptr, RES_X / 2 - 292,
	RES_Y / 3 + 34 * 17, T_C, "Special thanks to Stepan Nikitin: \
	github.com/nikitinste");
}
