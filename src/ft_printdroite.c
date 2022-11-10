/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printdroite.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 20:59:29 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/08 14:11:13 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_printsamey(t_rt *rt, t_coord one, t_coord two)
{	
	if (two.x > one.x)
		ft_swap(&one.x, &two.x);
	while (one.x >= two.x)
	{
		ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y, one.color));
		one.x--;
	}
}

void	ft_printdiagonefour(t_rt *rt, t_coord one, t_coord two)
{
	while (one.x != two.x)
	{
		ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y, one.color));
		one.x++;
		one.y++;
	}
	ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y, one.color));
}

void	ft_printdiagtwothree(t_rt *rt, t_coord one, t_coord two)
{
	while (one.x != two.x)
	{
		ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y, one.color));
		one.x++;
		one.y--;
	}
	ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y, one.color));
}

void	ft_printdiag(t_rt *rt, t_coord one, t_coord two)
{
	if (one.x - two.x == one.y - two.y)
	{
		if (two.x < one.x && two.y < one.y)
			ft_swapcoord(&one, &two);
		ft_printdiagonefour(rt, one, two);
	}
	else
	{
		if (one.x > two.x)
			ft_swapcoord(&one, &two);
		ft_printdiagtwothree(rt, one, two);
	}
}

void	ft_printsamex(t_rt *rt, t_coord one, t_coord two)
{
	if (one.x == two.x)
	{
		if (two.y > one.y)
			ft_swap(&one.y, &two.y);
		while (one.y >= two.y)
		{
			ft_printpixelimg(rt, ft_makecoord(rt, one.x, one.y, one.color));
			one.y--;
		}
	}
}
