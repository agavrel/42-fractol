/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorytms.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 11:42:03 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/18 15:51:21 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractol.h"

/*
** Mandelbrot is a specific case of Julia, same for Phoenix.
** d->min is the base offset while d->max is the maximum to iterate to.
*/

void	init_julia_set(t_3d *d)
{
	if (d->fractal == JULIA)
	{
		d->zoom = 300;
		d->max = 300;
		remarkable_julias(d);
	}
	else if (d->fractal == MANDELBROT)
	{
		d->max = 80;
		d->zoom = 280;
	}
	else if (d->fractal == FLOWERBROT)
	{
		d->max = 100;
		d->zoom = 300;
		d->color = 2;
	}
	else if (d->fractal == PHOENIX)
	{
		d->max = 80;
		d->zoom = 250;
	}
}

/*
** Mathematician Adrien Douady's tribute to his peer Benoit Mandelbrot.
** https://en.wikipedia.org/wiki/Mandelbrot_set
*/

void	mandelbrot(t_3d *d, t_cnb z, t_cnb c, int *i)
{
	double	n;
	double	t;

	n = z.real * z.real + z.imag * z.imag;
	t = 0;
	while (++(*i) < d->max && n < 4)
	{
		t = z.real;
		z.real = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2 * z.imag * t + c.imag;
		n = z.real * z.real + z.imag * z.imag;
	}
}

/*
** d->rng is a random value that will produce different remarkable Julias
** each time the user chooses Julia it refreshes Julia initialization
*/

void	remarkable_julias(t_3d *d)
{
	if (!d->rng)
		d->julia = (t_cnb) {.real = -0.506667, .imag = 0.520000 };
	else if (d->rng == 1)
		d->julia = (t_cnb) {.real = 0.403333, .imag = 0.273333 };
	else if (d->rng == 2)
		d->julia = (t_cnb) {.real = 0.386667, .imag = 0.103333 };
	else if (d->rng == 3)
		d->julia = (t_cnb) {.real = -0.203333, .imag = -0.696667 };
	else if (d->rng == 4)
		d->julia = (t_cnb) {.real = 0.18, .imag = -0.566667 };
	else if (d->rng == 5)
		d->julia = (t_cnb) {.real = 0.371504, .imag = -0.153893 };
}

/*
** Gaston Maurice Julia's algorytm coined to create Julia fractals
** https://en.wikipedia.org/wiki/Julia_set
*/

void	julia(t_3d *d, t_cnb z, int *i)
{
	double	t;

	t = 0;
	while (++(*i) < d->max && z.real * z.real + z.imag * z.imag < 4)
	{
		t = z.real;
		z.real = t * t - z.imag * z.imag + d->julia.real;
		z.imag = 2 * z.imag * t + d->julia.imag;
	}
}

/*
** Phoenix fractal algorytm
*/

void	phoenix(t_3d *d, t_cnb z, t_cnb c, int *i)
{
	double	n;
	t_cnb	t;

	n = z.real * z.real + z.imag * z.imag;
	t = (t_cnb) {.real = 0, .imag = 0};
	while (++(*i) < d->max && n < 4)
	{
		z.imag = 2 * fabs(z.imag * z.real) + c.imag;
		z.real = t.real - t.imag - c.real;
		t.real = z.real * z.real;
		t.imag = z.imag * z.imag;
		n = t.real + t.imag;
	}
}
