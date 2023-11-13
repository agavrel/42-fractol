/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 05:47:09 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/18 15:47:12 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractol.h"

/*
** padding function
** Also handle max iteration at smooth increase/decrease with
**  and d->max += sqrt(d->max + 1);
*/

static void	set_padding_imax(int k, t_3d *d)
{
	short	offset;

	offset = 40;
	if (k == KEY_UP)
		d->offset.y += -offset;
	else if (k == KEY_DOWN)
		d->offset.y += offset;
	else if (k == KEY_RIGHT)
		d->offset.x += offset;
	else if (k == KEY_LEFT)
		d->offset.x += -offset;
	if (k == KEY_PAD_ADD)
		d->max += (int)sqrt(d->max + 1);
	else if (k == KEY_PAD_SUB && d->max > 0)
		d->max -= (int)sqrt(d->max + 1);
}

/*
** Clear image function
*/

void		ft_black_screen(t_3d *d)
{
	t_index	i;

	i.y = 0;
	while (i.y < HEIGHT)
	{
		i.x = 0;
		while (i.x < WIDTH)
		{
			put_pixel_in_img(d, i.x, i.y, 0);
			++i.x;
		}
		++i.y;
	}
	mlx_put_image_to_window(d->img.mlx, d->img.win, d->img.image, 0, 0);
}

/*
** Change fractal function
** d->rng will generate different kind of Julias
*/

static void	set_fractal(int k, t_3d *d)
{
	if (k >= KEY_1 && k <= KEY_5)
	{
		if (k == KEY_5)
		{
			d->fractal = BARNSLEY;
			(!(d->a)) ? ft_black_screen(d) : ++d->a;
			d->max = 5000;
			fractol(d);
		}
		else
		{
			if (k == KEY_1)
				d->fractal = MANDELBROT;
			else if (k == KEY_2)
				d->fractal = JULIA;
			else if (k == KEY_3)
				d->fractal = PHOENIX;
			else
				d->fractal = FLOWERBROT;
			d->rng = random() % 6;
			init_julia_set(d);
		}
	}
}

/*
** Color function
*/

static void	set_color(int k, t_3d *d)
{
	if (k >= KEY_PAD_0 && k <= KEY_PAD_7)
	{
		if (k == KEY_PAD_0)
			d->color = 0;
		else if (k == KEY_PAD_1)
			d->color = 1;
		else if (k == KEY_PAD_2)
			d->color = 2;
		else if (k == KEY_PAD_3)
			d->color = 3;
		else if (k == KEY_PAD_4)
			d->color = 4;
		else if (k == KEY_PAD_5)
			d->color = 5;
		else if (k == KEY_PAD_6)
			d->color = 6;
		else
			d->color = 7;
	}
}

/*
** key hook
** space is to activate / unactive motion hook
*/

#include <stdio.h>
int			key_hook(int k, t_3d *d)
{
	if (k == KEY_SPACE)
		d->julia_static = (!d->julia_static) ? 1 : 0;
	if (k == KEY_ESCAPE)
	{
		mlx_destroy_image(d->img.mlx, d->img.image);
		exit(0);
	}
	if (k == KEY_H)
		d->menu = d->menu ? 0 : 1;
	set_padding_imax(k, d);
	set_fractal(k, d);
	set_color(k, d);
	mlx_destroy_image(d->img.mlx, d->img.image);
	init_img(d);
	fractol(d);
	return (k);
}
