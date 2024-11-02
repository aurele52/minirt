/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printdroite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 20:59:29 by audreyer          #+#    #+#             */
/*   Updated: 2023/01/09 22:48:17 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"


void	ft_swapcoord(t_coord *a, t_coord *b)
{
	t_coord	mem;

	mem = *a;
	*a = *b;
	*b = mem;
}

void	ft_swap(double *a, double *b)
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
		ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y), color);
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
void	ft_bresenhamthreesix(t_rt *rt, t_coord one, t_coord two, t_color color)
{
	int	e;
	int	dy;
	int	dx;

	dx = two.x - one.x;
	dy = two.y - one.y;
	e = dx;
	dx = e * 2;
	dy = dy * 2;
	while (1)
	{
		ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y), color);
		one.x++;
		if (one.x == two.x)
			break ;
		e = e + dy;
		if (e < 0)
		{
			one.y--;
			e = e + dx;
		}
	}
}

void	ft_bresenhamfourfive(t_rt *rt, t_coord one, t_coord two, t_color color)
{
	int	e;
	int	dy;
	int	dx;

	dx = two.x - one.x;
	dy = two.y - one.y;
	e = dx;
	dx = e * 2;
	dy = dy * 2;
	while (1)
	{
		ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y), color);
		one.x++;
		if (one.x == two.x)
			break ;
		e = e - dy;
		if (e < 0)
		{
			one.y++;
			e = e + dx;
		}
	}
}

void	ft_bresenhamtwoseven(t_rt *rt, t_coord one, t_coord two, t_color color)
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
		ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y), color);
		one.y--;
		if (one.y == two.y)
			break ;
		e = e + dx;
		if (e > 0)
		{
			one.x++;
			e = e + dy;
		}
	}
}

void	ft_bresenham(t_rt *rt, t_coord one, t_coord two, t_color color)
{
	int	dx;
	int	dy;

	if (two.x - one.x < 0)
		ft_swapcoord(&one, &two);
	dx = two.x - one.x;
	dy = two.y - one.y;
	if (dy != 0)
	{
		if (dy > 0)
		{
			if (dx >= dy)
				ft_bresenhamfourfive(rt, one, two, color);
			else
				ft_bresenhamoneeight(rt, one, two, color);
		}
		else
		{
			if (dx >= -dy)
				ft_bresenhamthreesix(rt, one, two, color);
			else
				ft_bresenhamtwoseven(rt, one, two, color);
		}
	}
	ft_printpixelimg(rt, ft_makecoord(rt, two.x, two.y), color);
}

void	ft_printdroite(t_rt *rt, t_coord one, t_coord two, t_color color)
{
	if (one.x == two .x)
		ft_printsamex(rt, one, two, color);
	else if (one.y == two.y)
		ft_printsamey(rt, one, two, color);
	else if (ft_abs(one.x - two.x) == ft_abs(one.y - two.y))
		ft_printdiag(rt, one, two, color);
	else
		ft_bresenham(rt, one, two, color);
}

void	ft_swapy(t_coord *one, t_coord *two)
{
	float	mem;

	mem = one->y;
	one->y = two->y;
	two->y = mem;
}

void	ft_swapx(t_coord *one, t_coord *two)
{
	float	mem;

	mem = one->x;
	one->x = two->x;
	two->x = mem;
}

void	ft_printsamey(t_rt *rt, t_coord one, t_coord two, t_color color)
{	
	if (two.x > one.x)
		ft_swapx(&one, &two);
	while (one.x >= two.x)
	{
		ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y), color);
		one.x--;
	}
}

void	ft_printdiagonefour(t_rt *rt, t_coord one, t_coord two, t_color color)
{
	while (one.x != two.x)
	{
		ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y), color);
		one.x++;
		one.y++;
	}
	ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y), color);
}

void	ft_printdiagtwothree(t_rt *rt, t_coord one, t_coord two, t_color color)
{
	while (one.x != two.x)
	{
		ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y), color);
		one.x++;
		one.y--;
	}
	ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y), color);
}

void	ft_printdiag(t_rt *rt, t_coord one, t_coord two, t_color color)
{
	if (one.x - two.x == one.y - two.y)
	{
		if (two.x < one.x && two.y < one.y)
			ft_swapcoord(&one, &two);
		ft_printdiagonefour(rt, one, two, color);
	}
	else
	{
		if (one.x > two.x)
			ft_swapcoord(&one, &two);
		ft_printdiagtwothree(rt, one, two, color);
	}
}

void	ft_printsamex(t_rt *rt, t_coord one, t_coord two, t_color color)
{
	if (one.x == two.x)
	{
		if (two.y > one.y)
			ft_swapy(&one, &two);
		while (one.y >= two.y)
		{
			ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y), color);
			one.y--;
		}
	}
}
