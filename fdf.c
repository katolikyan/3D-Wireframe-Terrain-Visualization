/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 13:07:32 by tkatolik          #+#    #+#             */
/*   Updated: 2019/06/10 15:16:16 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int				main(int ac, char **av)
{
	t_glob		*prms;

	if (ac != 2)
	{
		write(1, "usage: ./fdf [source file]\n", 28);
		return (0);
	}
	prms = ft_memalloc(sizeof(t_glob));
	prms->mlx_ptr = mlx_init();
	prms->win_ptr = mlx_new_window(prms->mlx_ptr, RES_X, RES_Y,
		   			"WIRE FRAME MAP");
	set_defoult_params(prms);
	get_source_data(prms, av[1]);
	new_image(prms);
	redraw(prms);
//	hoooks:
	mlx_hook(prms->win_ptr, 2, 0, &key_press, (void *)prms);
	mlx_hook(prms->win_ptr, 3, 0, &key_release, (void *)prms);
	mlx_hook(prms->win_ptr, 4, 0, &mouse_press, (void *)prms);
	mlx_hook(prms->win_ptr, 6, 0, &mouse_move, (void *)prms);
	mlx_hook(prms->win_ptr, 5, 0, &mouse_release, (void *)prms);
	mlx_hook(prms->win_ptr, 17, 0, &close_window, (void *)prms);
	mlx_loop(prms->mlx_ptr);
	return (0);
}

void			new_image(t_glob *prms)
{
	(prms->img_data).b_p_p = 4;
	(prms->img_data).l_s = RES_X * 4;
	(prms->img_data).e = 0;
	prms->img_data.img_ptr = mlx_new_image(prms->mlx_ptr, RES_X, RES_Y);
	prms->img_data.img_addr = mlx_get_data_addr(prms->img_data.img_ptr, 
			&(prms->img_data.b_p_p), &(prms->img_data.l_s),
		   	&(prms->img_data.e));
}
	
void			set_defoult_params(t_glob *prms)
{
	prms->trigger.info = 1;
	B_C		= DEF_BACK_C;			//0x2a2a2a;
	T_C		= DEF_TXT_C;			//0xe0e0e0;
	BASE_C	= DEF_BS_C; 			//0xe8e8e8;
	TOP_C	= DEF_TOP_C;			//0xff0043;
	SC		= DEF_SC;
	SC_MULT = 1;
	AX		= DEF_AX;
	AY		= DEF_AY;
	AZ		= DEF_AZ;
	FOCAL	= DEF_FOCAL;
	BACK_A	= DEF_BACK_A;
	PIX_A	= DEF_PIX_A;
}

void			redraw(t_glob *prms)
{
	redefine_colors(prms);
	if (prms->trigger.help)
	{
		mlx_put_image_to_window(prms->mlx_ptr, prms->win_ptr,
		 					prms->img_data.img_ptr, 0, 0);
		create_help(prms);
	}
	else
	{
		create_image(prms);
		mlx_put_image_to_window(prms->mlx_ptr, prms->win_ptr,
		 					prms->img_data.img_ptr, 0, 0);
		if (prms->trigger.info)
			create_info(prms);
	}
}

void		redefine_colors(t_glob *prms)
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
	if (prms->trigger.depth == 1)
		calc_depth(prms);
//	put background in window first of all for clean depth of field;
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
