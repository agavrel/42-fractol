#include "../incl/fractol.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdio.h>

int		main(void)
{
	void	*mlx;
	void	*win;
	void	*img;

	mlx = mlx_init();
	win = mlx_new_window(mlx, 900, 800, "Barnsley Fractall");
	img = mlx_new_image(mlx, WIDTH, HEIGHT);

	float	rng;
	long	n;
	t_index	i;
	t_cnb c;

	c = (t_cnb) {.real = 0, .imag = 0};

	float prob[4] = {0.01, 0.06, 0.08, 0.85};
	n = 500000;
	while (n--)
	{
		rng = ((float)rand())/RAND_MAX;
		if (rng <= 0.01f)
		{
			c.real= 0;
			c.imag = 0.16f * c.imag;
		}
		else if (rng <= 0.06f){

			c.real = -0.15f *c.real + 0.28f * c.imag;
			c.imag = 0.26f *c.real + 0.24f * c.imag+ 0.44f;
		}
		else if (rng <= 0.14f)
		{
			c.real = 0.2f * c.real + -0.26f * c.imag;
			c.imag = 0.23f * c.real + 0.22f * c.imag + 1.6f;
		}
		else
		{
			c.real = 0.85 * c.real + 0.04 * c.imag;
			c.imag = -0.04 * c.real + 0.85 * c.imag+ 1.6;
		}
		i.x=(c.real+3)*70;
		i.y= 800 - c.imag * 70; // replace 800 with height
		mlx_pixel_put(mlx, win, (int)i.x, (int)i.y, LIME);
	}
	mlx_loop(mlx);
	return (0);
}
