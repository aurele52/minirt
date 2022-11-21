/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printdroite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 20:59:29 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/21 20:36:39 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

void	ft_printsamey(t_rt *rt, t_coord one, t_coord two, int color)
{	
	if (two.x > one.x)
		ft_swapx(&one, &two);
	while (one.x >= two.x)
	{
		ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y, 0), color);
		one.x--;
	}
}

void	ft_printdiagonefour(t_rt *rt, t_coord one, t_coord two, int color)
{
	while (one.x != two.x)
	{
		ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y, 0), color);
		one.x++;
		one.y++;
	}
	ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y, 0), color);
}

void	ft_printdiagtwothree(t_rt *rt, t_coord one, t_coord two, int color)
{
	while (one.x != two.x)
	{
		ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y, 0), color);
		one.x++;
		one.y--;
	}
	ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y, 0), color);
}

void	ft_printdiag(t_rt *rt, t_coord one, t_coord two, int color)
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

void	ft_printsamex(t_rt *rt, t_coord one, t_coord two, int color)
{
	if (one.x == two.x)
	{
		if (two.y > one.y)
			ft_swapy(&one, &two);
		while (one.y >= two.y)
		{
			ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y, 0), color);
			one.y--;
		}
	}
}
