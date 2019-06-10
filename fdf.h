/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkatolik <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/21 18:30:10 by tkatolik          #+#    #+#             */
/*   Updated: 2019/06/10 00:59:36 by tkatolik         ###   ########.fr       */
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
*/

// resolution: 		minimum recomended resolution is 1920 x 1080;
# define RES_X		2560
# define RES_Y		1440

# define DEF_SC		30			// basic scale;
# define DEF_AX		-1.0		// basic angle x, y, z;
# define DEF_AY		0.0		
# define DEF_AZ		0.75
# define DEF_SHX	0			// basic shift;
# define DEF_SHY	0
# define DEF_FOCAL	2000
# define DEF_BACK_A 0			// basic alpha for background;
# define DEF_PIX_A	0			// basic alpha for pixels;

# define DEF_BACK_C	0x2a2a2a 	// background color;
# define DEF_BS_C	0xe8e8e8 	// base color;
# define DEF_BS_C_2	0x0f0f0f	// base color inverse (light background)
# define DEF_TOP_C	0xff0043	// hights color;
# define DEF_TXT_C	0xe0e0e0	// text color;
# define DEF_TXT_2	0x191919	// text color inverse (light background)

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

typedef struct		s_line
{
	int				x0;
	int				y0;
	int				c0;				// z called c because used as color info;
	double			z0;				// converted z0;
	int				x1;
	int				y1;
	int				c1;
	double			z1;				// converted z1;
	int				out;			// if both ccordinates are out of window;
}					t_line;

typedef struct		s_img_data
{
	void			*img_ptr;		
	char			*img_addr;
	int				b_p_p;			// bits per point;
	int				l_s;			// line_size;
	int				e;				
	int				background;		// background color;
	int				text_color;
	int				base_color;		// color of the maps base;
	int				top_color;		// color of the maps hights;
	unsigned char	back_alpha;	
	unsigned char	pix_alpha;	
}					t_img_data;

typedef struct	s_triggers
{
	char			mouse_3_press;	// bool for scroll pressed;
	t_xy			mouse_xy;		// storing base coordinates of mouse press;
	char			mouse_1_press;	// bool for L click pressed;
	char			perspective;	// bool for perspective;
	int				focal_lenght;	// describe focal lenght for perspective;
	char			distortion_1;	// art distortion projection 1;
	char			distortion_2;	// art distortion projection 2;
	char			distortion_3;	// art distortion projection 3;
	char			depth;			// bool for depth effect;
	char			info;			// bool for view info;
	char			help;			// bool for view help;
	int				scale_mult;		// scale multiplyer for scroll;
	int				m_blur;			// motion blur;
}					t_triggers;

typedef struct		s_global
{
	int				fd;
	void			*mlx_ptr;
	void			*win_ptr;
	t_img_data		img_data;
	int				**map_z;		// Z coordinates table;
	double			**map_z_adj;	// Z coordinates adjustable to scale Z;
	double			**map_z_prjct;	// converted Z in window cords, (depth);
	int				map_x;			// map demensions;
	int				map_y;	
	int				scale;
	int				clr_h_max;		// max and min H of the map;
	int				clr_h_min;
	t_rgb_kb		coeff_k;		// foefficioents of RGB liniars dependeses
	t_rgb_kb		coeff_b;
	t_rgb			clr_min;		// min and max colors for gradionts;
	t_rgb			clr_max;
	t_xy			crt;			// current xy coordinates from the map;
	double			angl_x; 		// angles for every axis rotation;
	double			angl_y;
	double			angl_z;
	t_xy			shift_xy; 		// shift for mooving the figure;
	t_triggers		trigger;		// trigers for hooks and view modes;
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

int 				key_press(int keycode, void *prm);
int					key_release(int	key, void *prm);
int 				mouse_press(int button, int x, int y, void *prm);
int 				mouse_release(int key, int x, int y, void *prm);
int					mouse_move(int x, int y, void *param);
int					close_window(void *prm);
int 				mlx_hook(void *win_ptr, int x_event,\
						int x_mask, int (*funct)(), void *prm);

/*
**	UTIL 
*/

int					ft_2d_int_array_min(int **arr, int h, int i);
int					ft_2d_int_array_max(int **arr, int h, int i);
double				ft_2d_double_array_max(double **arr, int h, int i);
double				ft_2d_double_array_min(double **arr, int h, int i);

#endif
