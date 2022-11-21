/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printdroite3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 21:02:08 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/21 19:50:15 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_coord	*ft_makecoord(t_rt *rt, int x, int y)
{
	t_coord	*coord;

	coord = ft_malloc(sizeof(t_coord), rt->garbage);
	if (!coord)
		ft_exit(rt, "malloc error\n");
	coord->x = x;
	coord->y = y;
	return (coord);
}

void	ft_swapcoord(t_coord *a, t_coord *b)
{
	t_coord	mem;

	mem = *a;
	*a = *b;
	*b = mem;
}

void	ft_swap(int *a, int *b)
{
	int	mem;

	mem = *a;
	*a = *b;
	*b = mem;
}

void	ft_bresenhamoneeight(t_rt *rt, t_coord one, t_coord two, int color)
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
