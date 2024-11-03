/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printsp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 19:48:55 by audreyer          #+#    #+#             */
/*   Updated: 2023/01/09 22:49:06 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/rt.h"

void drawCircle(t_rt *rt, double x0, double y0, double radius, t_color color) {
	if (TEST == 1) {
		x0 = (((x0 + 5.14) / (9.56 + 5.14)) * 800) + 100;
		y0 = ((1 - ((y0 - 41.32) / (51.09 - 41.32))) * 800) + 100;
	}
	if (TEST == 3) {
		x0 = (((x0 - 1.3) / (3.7 - 1.3)) * 800) + 100;
		radius = radius * 400;
		y0 = ((1 - ((y0 - 47.9) / (49.3 - 47.9))) * 800) + 100;
	}
	int x = radius;
    int y = 0;
    int decisionOver2 = 1 - x;

    while (y <= x) {
        ft_printpixelimg(rt, ft_makecoord(rt, x + x0, y + y0), color);  // Octant 1
        ft_printpixelimg(rt, ft_makecoord(rt, y + x0, x + y0), color);  // Octant 2
        ft_printpixelimg(rt, ft_makecoord(rt, -x + x0, y + y0), color); // Octant 4
        ft_printpixelimg(rt, ft_makecoord(rt, -y + x0, x + y0), color); // Octant 3
        ft_printpixelimg(rt, ft_makecoord(rt, -x + x0, -y + y0), color); // Octant 5
        ft_printpixelimg(rt, ft_makecoord(rt, -y + x0, -x + y0), color); // Octant 6
        ft_printpixelimg(rt, ft_makecoord(rt, x + x0, -y + y0), color);  // Octant 7
        ft_printpixelimg(rt, ft_makecoord(rt, y + x0, -x + y0), color);  // Octant 8
        y++;

        if (decisionOver2 <= 0) {
            decisionOver2 += 2 * y + 1;
        } else {
            x--;
            decisionOver2 += 2 * (y - x) + 1;
        }
    }
}

void	ft_printLycee(t_rt *rt, t_lycee *sp)
{
	if (sp->coord.x != 0 && sp->coord.y != 0)
	drawCircle(rt, sp->coord.x, sp->coord.y, sp->rayon, sp->color);
}
