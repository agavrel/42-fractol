/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 12:37:49 by angavrel          #+#    #+#             */
/*   Updated: 2017/03/16 15:08:01 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractol.h"

/*
** Main program
** will put image to window once drawn and menu
*/

void	fractol(t_3d *d)
{
	if (d->fractal == BARNSLEY)
		fern_fractal(d);
	else
	{
		d->min.x = ((d->offset.x + (WIDTH >> 1)) / (d->zoom / 2)) / -2;
		d->min.y = ((d->offset.y + (HEIGHT >> 1)) / (d->zoom / 2)) / -2;
		d->i.y = 0;
		while (d->i.y < HEIGHT)
		{
			d->i.x = -1;
			while (++d->i.x < WIDTH)
				draw_fractal(d);
			++d->i.y;
		}
	}
	mlx_put_image_to_window(d->img.mlx, d->img.win, d->img.image, 0, 0);
	if (d->menu)
		settings_background(d);
}

/*
** depending on chosen fractal will display it to the screen
*/

void	draw_fractal(t_3d *d)
{
	t_cnb		z;
	t_cnb		c;
	int			i;
	unsigned	in_color;

	c.real = d->i.x / d->zoom + d->min.x;
	c.imag = d->i.y / d->zoom + d->min.y;
	z = (t_cnb) {.real = 0, .imag = 0};
	i = -1;
	in_color = (d->color != 5) ? CRIMSON : BLACK;
	if (d->fractal == MANDELBROT)
		mandelbrot(d, z, c, &i);
	else if (d->fractal == JULIA)
		julia(d, c, &i);
	else if (d->fractal == FLOWERBROT)
		mandel_flower(d, z, c, &i);
	else if (d->fractal == PHOENIX)
	{
		in_color = 0xffffff;
		phoenix(d, z, c, &i);
	}
	(i == d->max) ? put_pixel_in_img(d, d->i.x, d->i.y, in_color) :
		put_pixel_in_img(d, d->i.x, d->i.y, color_pixel(d, i));
}

/*
** Initialize image
*/

void	init_img(t_3d *d)
{
	int		bpp;
	int		sizeline;
	int		endian;

	d->img.image = mlx_new_image(d->img.mlx, WIDTH, HEIGHT);
	d->img.data = mlx_get_data_addr(d->img.image, &bpp, &sizeline, &endian);
	d->img.bpp = bpp;
	d->img.sizeline = sizeline;
	d->img.endian = endian;
}

/*
** Put pixel inside the image.
** shifting right 3 bits (>> 3) is a binary operation equivalent to (/ 8).
** casting the memory address into int * and then dereferencing is to speed up
*/

void	put_pixel_in_img(t_3d *d, int x, int y, int color)
{
	if (x >= 0 && y >= 0 && x < WIDTH && y < HEIGHT)
		*(int *)&d->img.data[(x * d->img.bpp >> 3) +
			(y * d->img.sizeline)] = color;
}
