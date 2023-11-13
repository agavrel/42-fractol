#include "../incl/fractol.h"

float	ft_fclamp(float n, float min, float max)
{
	if (n < min)
		return (min);
	return (n > max ? max : n);
}

t_rgb	ft_hex2rgb(int hex)
{
	t_rgb	rgb;

	rgb.r = (hex >> 16) & 0xFF;
	rgb.g = (hex >> 8) & 0xFF;
	rgb.b = hex & 0xFF;
	return (rgb);
}

t_rgb	ft_hsb2rgb(t_hsb hsv)
{
	t_rgb		rgb;
	t_vector	i;

	i.w = (int)(hsv.h / 60);
	i.w = (hsv.h / 60) - i.w;
	i.x = 0xff * (hsv.b * (1 - hsv.s));
	i.y = 0xff * (hsv.b * (1 - i.w * hsv.s));
	i.z = 0xff * (hsv.b * (1 - (1 - i.w) * hsv.s));
	hsv.b *= 0xff;
	hsv.h = (int)((hsv.h) / 60);
	if (hsv.h == 0)
		rgb = (t_rgb) {.r = hsv.b, .g = i.z, .b = i.x};
	else if (hsv.h == 1)
		rgb = (t_rgb) {.r = i.y, .g = hsv.b, .b = i.x};
	else if (hsv.h == 2)
		rgb = (t_rgb) {.r = i.x, .g = hsv.b, .b = i.z};
	else if (hsv.h == 3)
		rgb = (t_rgb) {.r = i.x, .g = i.y, hsv.b};
	else if (hsv.h == 4)
		rgb = (t_rgb) {.r = i.z, .g = i.x, hsv.b};
	else if (hsv.h == 5)
		rgb = (t_rgb) {.r = hsv.b, .g = i.x, .b = i.y};
	else
		rgb = (t_rgb) {.r = 0, .g = 0, .b = 0};
	return (rgb);
}

int		ft_rgb2hex(t_rgb rgb)
{
	return (((int)rgb.r << 16) + ((int)rgb.g << 8) + rgb.b);
}

int		ft_hsb2hex(t_hsb hsv)
{
	return (ft_rgb2hex(ft_hsb2rgb(hsv)));
}