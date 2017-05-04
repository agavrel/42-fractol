/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <angavrel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 04:03:25 by angavrel          #+#    #+#             */
/*   Updated: 2017/02/10 23:01:24 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/fractol.h"

/*
** main program: Initialize fractals, draw chosen fractal and awaits user input
*/

int		main(int ac, char **av)
{
	t_3d	d;

	if (ac != 2 || !init_fractal(&d, av[1]))
	{
		ft_putendl("\033[32mUsage: ./fractol Fractal, i.e: ./fractol Barnsley");
		ft_putendl("[Mandelbrot] [Julia] [Phoenix] [Barnsley] [Flowerbrot]");
		exit(-1);
	}
	else if (!(init_variables(&d)))
		ft_error("Failed to initialize variables");
	fractol(&d);
	mlx_mouse_hook(d.img.win, mouse_scaling_hook, &d);
	mlx_hook(d.img.win, 2, 4, key_hook, &d);
	mlx_hook(d.img.win, 6, 1 << 8, motion_hook, &d);
	mlx_loop(d.img.mlx);
	return (0);
}

/*
** initialize variables for later use
*/

int		init_variables(t_3d *d)
{
	if (!(d->img.mlx = mlx_init()))
		ft_error("Mlx initialization failed");
	if (!(d->img.win = mlx_new_window(d->img.mlx, WIDTH, HEIGHT, TITLE)))
		ft_error("Window creation failed");
	init_img(d);
	if (!d->img.image)
		ft_error("Image creation failed");
	d->zoom = 200;
	d->color = 0;
	d->menu = 0;
	d->offset = (t_i) {.x = 0, .y = 0};
	d->a = 0;
	init_julia_set(d);
	return (1);
}

/*
** set fractal chosen by user
*/

int		init_fractal(t_3d *d, char *name)
{
	if (!ft_strcmp(name, "Mandelbrot"))
		d->fractal = MANDELBROT;
	else if (!ft_strcmp(name, "Phoenix"))
		d->fractal = PHOENIX;
	else if (!ft_strcmp(name, "Julia"))
		d->fractal = JULIA;
	else if (!ft_strcmp(name, "Barnsley"))
		d->fractal = BARNSLEY;
	else if (!ft_strcmp(name, "Flowerbrot"))
		d->fractal = FLOWERBROT;
	else
		return (0);
	return (1);
}
