/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printdroite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 20:59:29 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/20 19:44:23 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_printsamey(t_rt *rt, t_coord one, t_coord two, int color)
{	
	if (two.x > one.x)
		ft_swap(&one.x, &two.x);
	while (one.x >= two.x)
	{
		ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y), color);
		one.x--;
	}
}

void	ft_printdiagonefour(t_rt *rt, t_coord one, t_coord two, int color)
{
	while (one.x != two.x)
	{
		ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y), color);
		one.x++;
		one.y++;
	}
	ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y), color);
}

void	ft_printdiagtwothree(t_rt *rt, t_coord one, t_coord two, int color)
{
	while (one.x != two.x)
	{
		ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y), color);
		one.x++;
		one.y--;
	}
	ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y), color);
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
			ft_swap(&one.y, &two.y);
		while (one.y >= two.y)
		{
			ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y), color);
			one.y--;
		}
	}
}
