/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printdroite3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 21:02:08 by audreyer          #+#    #+#             */
/*   Updated: 2023/01/09 22:47:50 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_coord	ft_makecoord(t_rt *rt, float x, float y, float z)
{
	static t_coord	coord;

	(void)rt;
	coord.x = x;
	coord.y = y;
	coord.z = z;
	return (coord);
}

void	ft_swapcoord(t_coord *a, t_coord *b)
{
	t_coord	mem;

	mem = *a;
	*a = *b;
	*b = mem;
}

void	ft_swap(float *a, float *b)
{
	int	mem;

	mem = *a;
	*a = *b;
	*b = mem;
}

void	ft_bresenhamoneeight(t_rt *rt, t_coord one, t_coord two, t_color color)
{
	int	e;
	int	dy;
	int	dx;

	dx = two.x - one.x;
	dy = two.y - one.y;
	e = dy;
	dy = e * 2;
	dx = dx * 2;
	while (1)
	{
		ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y, 0), color);
		one.y++;
		if (one.y == two.y)
			break ;
		e = e - dx;
		if (e < 0)
		{
			one.x++;
			e = e + dy;
		}
	}
}
