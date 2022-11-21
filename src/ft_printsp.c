/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printsp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 19:48:55 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/21 20:37:21 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_printsp(t_rt *rt, t_sp *sp)
{
	int	x;
	int	y;
	int	m;
	x = 0;
	y = sp->rayon;
	m = 5 - 4 * sp->rayon;
	while (x <= y)
	{
		ft_printpixelimg(rt, ft_makecoord(rt, x + sp->coord->x, y + sp->coord->y, 0), sp->color);
		ft_printpixelimg(rt, ft_makecoord(rt, y + sp->coord->x, x + sp->coord->y, 0), sp->color);
		ft_printpixelimg(rt, ft_makecoord(rt, -x + sp->coord->x, y + sp->coord->y, 0), sp->color);
		ft_printpixelimg(rt, ft_makecoord(rt, -y + sp->coord->x, x + sp->coord->y, 0), sp->color);
		ft_printpixelimg(rt, ft_makecoord(rt, x + sp->coord->x, -y + sp->coord->y, 0), sp->color);
		ft_printpixelimg(rt, ft_makecoord(rt, y + sp->coord->x, -x + sp->coord->y, 0), sp->color);
		ft_printpixelimg(rt, ft_makecoord(rt, -x + sp->coord->x, -y + sp->coord->y, 0), sp->color);
		ft_printpixelimg(rt, ft_makecoord(rt, -y + sp->coord->x, -x + sp->coord->y, 0), sp->color);
		if (m > 0)
		{
			y = y - 1;
			m = m - 8 * y;
		}
		x++;
		m = m + 8 * x + 4;
	}
}
