/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angavrel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/24 00:12:02 by angavrel          #+#    #+#             */
/*   Updated: 2016/12/24 00:12:14 by angavrel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include "libft.h"

char	*ft_dtoa(double n, int precision)
{
	char	*s;
	long	tmp;
	long	t;
	int		length;

	if (!precision)
		return (ft_itoa((int)n));
	tmp = (n * pow(10, precision));
	t = (tmp < 0) ? -tmp : tmp;
	length = (n <= 0 ? 3 : 2);
	while (tmp && ++length)
		tmp /= 10;
	if (!(s = (char *)malloc(sizeof(char) * length)))
		return (NULL);
	s[--length] = '\0';
	if (tmp <= 0)
		s[0] = (tmp < 0 ? '-' : '0');
	while (t)
	{
		s[--length] = (!precision--) ? '.' : t % 10 + '0';
		t /= (precision + 1) ? 10 : 1;
	}
	return (s);
}
