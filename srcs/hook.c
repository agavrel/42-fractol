/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 05:55:43 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/08 02:24:02 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractol.h"

static void	settings(t_3d *d, unsigned color)
{
	short		x;

	x = 15;
	mlx_string_put(d->img.mlx, d->img.win, x, 10, color,
			"Press 'H' to close help");
	mlx_string_put(d->img.mlx, d->img.win, x, 35, color,
			"West, East, North, South : [<-] [->] [^] [v]");
	mlx_string_put(d->img.mlx, d->img.win, x, 60, color,
			"Zoom : [Mouse wheel or right/left click]");
	mlx_string_put(d->img.mlx, d->img.win, x, 85, color,
			"Change Fractal : [1, 2, ...]");
	mlx_string_put(d->img.mlx, d->img.win, x, 110, color,
			"Change Color : [NUM PAD : 1, 2, ...]");
	mlx_string_put(d->img.mlx, d->img.win, x, 135, color,
			"Increase/Decrease current iteration : [+] [-]");
	mlx_string_put(d->img.mlx, d->img.win, x, 160, color,
			"Pause mouse motion : [SPACE]");
	mlx_string_put(d->img.mlx, d->img.win, x, 195, color,
			"Exit : [ESCAPE]");
}

void		settings_background(t_3d *d)
{
	t_index		i;
	int			y_max;
	unsigned	color;

	y_max = (d->menu == 1) ? 230 : 45;
	i.y = 0;
	color = 0xaa000000;
	while (i.y < y_max)
	{
		i.x = 0;
		while (i.x < WIDTH)
		{
			mlx_pixel_put(d->img.mlx, d->img.win, i.x, i.y, color);
			++i.x;
		}
		++i.y;
	}
	if (!d->menu)
		mlx_string_put(d->img.mlx, d->img.win, 15, 10, HELP_COLOR,
			"Display Menu : Press [H] Button");
	if (d->menu)
		settings(d, HELP_COLOR);
}

/*
** change julia's real number based on mouse position
*/

int			motion_hook(int x, int y, t_3d *d)
{
	if (x > 0 && x < WIDTH && y > 0 && y < HEIGHT && !d->julia_static)
	{
		d->julia.real = (x + d->offset.x) / (double)d->zoom + d->min.x;
		d->julia.imag = (y + d->offset.y) / (double)d->zoom + d->min.y;
		fractol(d);
	}
	return (1);
}

/*
** zooming function
*/

int			mouse_scaling_hook(int k, int x, int y, t_3d *d)
{
	float	scaling;

	scaling = 0;
	if ((k == 1 || k == 2 || k == 4 || k == 5) &&
	(x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT))
	{
		if (k == 4 || k == 1)
			scaling = 1.25;
		else if (k == 5 || k == 2)
			scaling = 0.8;
		if (k == 1 || k == 2)
		{
			d->offset.x = round(d->offset.x + ((WIDTH >> 1) - x) * scaling);
			d->offset.y = round(d->offset.y + ((HEIGHT >> 1) - y) * scaling);
		}
		d->zoom *= scaling;
		fractol(d);
	}
	return (1);
}
