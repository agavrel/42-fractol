/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorytms2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 11:02:54 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/18 15:52:06 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractol.h"

/*
** Michael Barnsley coined this algorytm that creates a fern fractal
** https://en.wikipedia.org/wiki/Barnsley_fern
*/

void	fern_fractal(t_3d *d)
{
	d->fractal = BARNSLEY;
	d->c = (t_cnb) {.real = 0, .imag = 0};
	barnsley_fern_algo(d, d->c, 0, 0);
}

/*
** 2% of the time c.real will be reset to 0 : if (rng <= 0.01f);
** Barnsley's algo iterates about 500k times to obtain a beautiful fern.
*/

void	barnsley_fern_algo(t_3d *d, t_cnb c, float rng, int i)
{
	while (++i < d->max * 100)
	{
		rng = ((float)rand()) / RAND_MAX;
		if (rng <= 0.01f)
		{
			c.real = 0;
			c.imag = 0.16f * c.imag;
		}
		else if (rng <= 0.06f)
		{
			c.real = -0.15f * c.real + 0.28f * c.imag;
			c.imag = 0.26f * c.real + 0.24f * c.imag + 0.44f;
		}
		else if (rng <= 0.15f)
		{
			c.real = 0.2f * c.real + -0.26f * c.imag;
			c.imag = 0.23f * c.real + 0.22f * c.imag + 1.6f;
		}
		else
			c = (t_cnb) {.real = 0.85f * c.real + 0.04f * c.imag,
				.imag = -0.04f * c.real + 0.85f * c.imag + 1.6f};
		d->c = (t_cnb) {.real = (c.real + 3) * 70, .imag = 800 - c.imag * 70};
		put_pixel_in_img(d, d->c.real + 300, d->c.imag - 50, LIME);
	}
}

void	mandel_flower(t_3d *d, t_cnb z, t_cnb c, int *i)
{
	double	n;
	double	t;

	n = pow(z.real, 6) + pow(z.imag, 6);
	t = 0;
	while (++(*i) < d->max && n < 4)
	{
		t = z.real;
		z.real = pow(z.real, 6) - (15 * pow(z.real, 4) * pow(z.imag, 2))
		+ (15 * pow(z.real, 2) * pow(z.imag, 4)) - pow(z.imag, 6) + c.imag;
		z.imag = (6 * pow(t, 5) * z.imag - 20 * pow(t, 3) * pow(z.imag, 3)
		+ 6 * t * pow(z.imag, 5)) + c.real;
		n = pow(z.real, 6) + pow(z.imag, 6);
	}
}
