/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:30:10 by tkatolik          #+#    #+#             */
/*   Updated: 2019/06/16 01:06:56 by tkatolik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

/*
** includes _______________________________________________________
*/

# include "./minilibx/mlx.h"
# include "./libft/inc/libft.h"
# include <math.h>

/*
** defines ________________________________________________________
** resolution: 		minimum recomended resolution is 1920 x 1080;
** 													 2560 x 1440;
*/

# define RES_X		1920
# define RES_Y		1080

# define DEF_SC		30
# define DEF_AX		-1.0
# define DEF_AY		0.0
# define DEF_AZ		0.75
# define DEF_SHX	0
# define DEF_SHY	0
# define DEF_FOCAL	2000
# define DEF_BACK_A 0
# define DEF_PIX_A	0

# define DEF_BACK_C	0x2a2a2a
# define DEF_BS_C	0xe8e8e8
# define DEF_BS_C_2	0x0f0f0f
# define DEF_TOP_C	0xff0043
# define DEF_TXT_C	0xe0e0e0
# define DEF_TXT_2	0x191919

/*
** Shortcats ______________________________________________________
*/

# define MAP_Z		((*prms).map_z)
# define MAP_Z_ADJ	((*prms).map_z_adj)
# define MAP_Z_NEW	((*prms).map_z_prjct)

# define X			(prms->crt.x)
# define Y			(prms->crt.y)

# define AX			(prms->angl_x)
# define AY			(prms->angl_y)
# define AZ			(prms->angl_z)

# define SHX		(prms->shift_xy.x)
# define SHY		(prms->shift_xy.y)

# define SC			(prms->scale)
# define SC_MULT	(prms->trigger.scale_mult)

# define IMG		(prms->img_data.img_addr)
# define B_C		(prms->img_data.background)
# define T_C		(prms->img_data.text_color)
# define BASE_C		(prms->img_data.base_color)
# define TOP_C		(prms->img_data.top_color)
# define BACK_A		(prms->img_data.back_alpha)
# define PIX_A 		(prms->img_data.pix_alpha)

# define BLUR		(prms->trigger.m_blur)
# define FOCAL		(prms->trigger.focal_lenght)

/*
** structs ________________________________________________________
*/

typedef struct		s_xy
{
	int				x;
	int				y;
}					t_xy;

typedef struct		s_rgb
{
	unsigned char	a;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

}					t_rgb;

typedef struct		s_rgb_kb
{
	float			a;
	float			r;
	float			g;
	float			b;

}					t_rgb_kb;

typedef struct		s_prjct
{
	float			c_x;
	float			c_y;
	float			tmp0;
	float			tmp1;
}					t_prjct;

typedef struct		s_line
{
	int				x0;
	int				y0;
	int				c0;
	double			z0;
	int				x1;
	int				y1;
	int				c1;
	double			z1;
	int				out;
}					t_line;

typedef struct		s_img_data
{
	void			*img_ptr;
	char			*img_addr;
	int				b_p_p;
	int				l_s;
	int				e;
	int				background;
	int				text_color;
	int				base_color;
	int				top_color;
	unsigned char	back_alpha;
	unsigned char	pix_alpha;
}					t_img_data;

typedef struct		s_triggers
{
	char			mouse_3_press;
	t_xy			mouse_xy;
	char			mouse_1_press;
	char			perspective;
	int				focal_lenght;
	char			distortion_1;
	char			distortion_2;
	char			distortion_3;
	char			depth;
	char			info;
	char			help;
	int				scale_mult;
	int				m_blur;
}					t_triggers;

typedef struct		s_global
{
	int				fd;
	void			*mlx_ptr;
	void			*win_ptr;
	t_img_data		img_data;
	int				**map_z;
	double			**map_z_adj;
	double			**map_z_prjct;
	int				map_x;
	int				map_y;
	int				scale;
	int				clr_h_max;
	int				clr_h_min;
	t_rgb_kb		coeff_k;
	t_rgb_kb		coeff_b;
	t_rgb			clr_min;
	t_rgb			clr_max;
	t_xy			crt;
	double			angl_x;
	double			angl_y;
	double			angl_z;
	t_xy			shift_xy;
	t_triggers		trigger;
}					t_glob;

/*
** functions _____________________________________________________
*/

void				new_image(t_glob *prms);
void				set_defoult_params(t_glob *prms);
void				get_source_data(t_glob *prms, char *source);
void				get_map_xy(t_glob *prms);
void				check_map(t_glob *prms, char *line);
void				get_map_z(t_glob *prms);
void				get_liniar_coefficients(t_glob *prms);
void				redefine_colors(t_glob *prms);
void				calc_depth(t_glob *prms);
void				redraw(t_glob *prms);

/*
** DRAW
*/

void				create_image(t_glob *prms);
void				create_info(t_glob *prms);
void				create_help(t_glob *prms);
void				altitude_info(t_glob *prms);
void				draw(t_glob *prms, t_line xy);
void				put_in_image(t_glob *prms, int x, int y, int c);
t_line				project(t_glob *prms, int d_x, int d_y);
void				perspective(t_glob *prms, t_line *xy);
void				distortion_1(t_glob *prms, t_line *xy);
void				distortion_2(t_glob *prms, t_line *xy);
void				distortion_3(t_glob *prms, t_line *xy);
int					color(t_glob *prms, t_line xy, int delta, int i);
int					depth(t_glob *prms, t_line xy, int delta, int i);

/*
**	HOOK
*/

int					key_press(int keycode, void *prm);
int					key_release(int	key, void *prm);
int					mouse_press(int button, int x, int y, void *prm);
int					mouse_release(int key, int x, int y, void *prm);
int					mouse_move(int x, int y, void *param);
int					close_window(void *prm);
int					mlx_hook(void *win_ptr, int x_event,\
						int x_mask, int (*funct)(), void *prm);

/*
** UTIL
*/

int					ft_2d_int_array_min(int **arr, int h, int i);
int					ft_2d_int_array_max(int **arr, int h, int i);
double				ft_2d_double_array_max(double **arr, int h, int i);
double				ft_2d_double_array_min(double **arr, int h, int i);

/*
** STATICS AND NORM EXTENTION
*/

void				redefine_colors_background(t_glob *prms);
void				get_map_xy_2(t_glob *prms, char *line);
void				get_map_z_extra(t_glob *prms);
void				color_2(t_glob *prms, t_line xy, t_rgb_kb *rgb, t_xy d_i);
void				project_z(t_glob *prms, t_line *new, \
												t_prjct *xy, t_xy *dxy);
void				project_y(t_glob *prms, t_line *new, \
												t_prjct *xy, t_xy *dxy);
void				project_x(t_glob *prms, t_line *new, \
												t_prjct *xy, t_xy *dxy);
void				transforms_shift_optimization(t_glob *prms, t_line *new);

int					key_press_0_altitude_reset(int key, t_glob *prms);
int					key_press_1_altitude(int key, t_glob *prms);
int					key_press_2_views(int key, t_glob *prms);
int					key_press_3_scale_rotation(int key, t_glob *prms);
int					key_press_4_background_clr_alpha(int key, t_glob *prms);
int					key_press_5_transformations(int key, t_glob *prms);
int					key_press_6_help_info(int key, t_glob *prms);
int					key_press_7_depth_focal_motion_blur(int key, t_glob *prms);
int					key_press_8_reset_close(int key, t_glob *prms);
void				create_info_0_distortions(t_glob *prms);
void				create_info_1_alpha(t_glob *prms);
void				create_info_2_scale_zoom(t_glob *prms);
void				create_info_3_focal_orto(t_glob *prms);
void				create_info_4_altitude_help(t_glob *prms);
void				create_help_2(t_glob *prms);
void				create_help_3(t_glob *prms);

#endif
