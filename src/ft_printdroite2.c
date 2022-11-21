/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printdroite2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 21:00:57 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/21 20:27:38 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_bresenhamthreesix(t_rt *rt, t_coord one, t_coord two, int color)
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
		ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y, 0), color);
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

void	ft_bresenhamfourfive(t_rt *rt, t_coord one, t_coord two, int color)
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
		ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y, 0), color);
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

void	ft_bresenhamtwoseven(t_rt *rt, t_coord one, t_coord two, int color)
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

void	ft_bresenham(t_rt *rt, t_coord one, t_coord two, int color)
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
	ft_printpixelimg(rt, ft_makecoord(rt, two.x, two.y, 0), color);
}

void	ft_printdroite(t_rt *rt, t_coord one, t_coord two, int color)
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
