/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/15 23:58:56 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/10 23:02:12 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include "../libmlx/mlx.h"
# include "../libft/includes/libft.h"
# include "keycode_mac.h"
# include "colors.h"

# define TITLE		"Fractol"
# define HEIGHT		800
# define WIDTH		1200
# define HELP_COLOR	0xffffff

enum	e_fractal{MANDELBROT, JULIA, PHOENIX, BARNSLEY, FLAME, FLOWERBROT};


/*
** stands for complex number
*/

typedef struct		s_cnb
{
	double			real;
	double			imag;
}					t_cnb;

/*
** structure used iterating put_pixel in img
*/

typedef struct		s_index
{
	int				x;
	int				y;
}					t_index;

/*
** colored 2d vector
*/

typedef	struct		s_cv
{
	double			x;
	double			y;
	unsigned		color;
}					t_cv;

/*
** structure to hold data about image
*/

typedef struct		s_image
{
	void			*mlx;
	void			*win;
	int				*image;
	char			*data;
	int				bpp;
	int				sizeline;
	int				endian;
}					t_image;

/*
** img is data relative to the image
** e_fractal is the name of the current fractal
** i is pixel nb and f is current iteration
** max is the maximum number to iterate
** offset is the padding
** zoom is the scaling
** julia_static is to activate the motion hook for Julia set
** fern are variables relative to Barnsley's algo
*/

typedef struct		s_3d
{
	t_image			img;
	enum e_fractal	fractal;
	t_index			i;
	int				max;

	t_i				min;
	double			zoom;
	t_i				offset;
	int				iter_coef;
	t_cnb			c_point;
	t_cnb			c;
	int				fern_i;
	int				julia_static;
	t_cnb			julia;
	int				color;
	int				menu;
	short			rng;
	short			a;
}					t_3d;

/*
** Parsing and variable t_3d initialization
*/

int					init_fractal(t_3d *d, char *name);
int					init_variables(t_3d *d);
void				init_img(t_3d *d);
void				put_pixel_in_img(t_3d *d, int x, int y, int color);
void				settings_background(t_3d *d);
void				ft_blackscreen(t_3d *d);

/*
** Fractol program
*/

void				fractol(t_3d *d);
void				draw_fractal(t_3d *d);
void				ft_draw_line(t_3d *d, t_cv a, t_cv b);

/*
** Fractals algorytms
*/

void				init_julia_set(t_3d *d);
void				mandelbrot(t_3d *d, t_cnb z, t_cnb c, int *i);
void				remarkable_julias(t_3d *d);
void				julia(t_3d *d, t_cnb c, int *i);
void				phoenix(t_3d *d, t_cnb z, t_cnb c, int *i);
void				fern_fractal(t_3d *d);
void				barnsley_fern_algo(t_3d *d, t_cnb c, float rng, int i);
void				mandel_flower(t_3d *d, t_cnb z, t_cnb c, int *i);

/*
** color functions
*/

unsigned			color_pixel(t_3d *d, int a);
unsigned			ft_rainbow_gradient(double x);

/*
** Hook to check for user input
*/

int					motion_hook(int x, int y, t_3d *d);
int					key_hook(int keycode, t_3d *d);
int					mouse_scaling_hook(int button, int x, int y, t_3d *d);

/*
** Color conversion
*/

t_rgb				ft_hex2rgb(int hex);
int					ft_rgb2hex(t_rgb rgb);
t_rgb				ft_hsb2rgb(t_hsb hsb);
int					ft_hsb2hex(t_hsb hsb);
int					ft_shade_color(int c, double n);
float				ft_fclamp(float n, float min, float max);

#endif
