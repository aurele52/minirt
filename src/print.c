#include "../include/rt.h"

void	swapcoord(t_coord *a, t_coord *b)
{
	t_coord	mem;

	mem = *a;
	*a = *b;
	*b = mem;
}

void	swap(double *a, double *b)
{
	int	mem;

	mem = *a;
	*a = *b;
	*b = mem;
}

void	printpixelimg(t_rt *rt, t_coord print, t_color color)
{
	int		pos;
	int		colorint;
	char	*pixel;

	if (print.x < 0 || print.y < 0
		|| print.y > rt->ysize || print.x > rt->xsize)
		return ;
	pos = ((int)print.y * rt->image.size_line
			+ (int)print.x * (rt->image.bits_per_pixel / 8));
	pixel = rt->image.imgaddress + pos;
	colorint = colorToInt(&color);
	*(int *)pixel = colorint;
}

void	printseg(t_rt *rt, t_seg *seg)
{
	printdroite(rt, (*seg).first, (*seg).second, (*seg).color);
}

void	printSquare(t_rt *rt, t_square *square)
{
	t_coord	third;
	t_coord	fourth;

	if (TEST == 1) {
		square->first.x = (((square->first.x + 5.14) / (9.56 + 5.14)) * 800) + 100;
		square->first.y = ((1 - ((square->first.y - 41.32) / (51.09 - 41.32))) * 800) + 100;
		square->second.x = (((square->second.x + 5.14) / (9.56 + 5.14)) * 800) + 100;
		square->second.y = ((1 - ((square->second.y - 41.32) / (51.09 - 41.32))) * 800) + 100;
	}
	if (TEST == 3) {
		square->first.x = (((square->first.x - 1.3) / (3.7 - 1.3)) * 800) + 100;
		square->first.y = ((1 - ((square->first.y - 47.9) / (49.3 - 47.9))) * 800) + 100;
		square->second.x = (((square->second.x - 1.3) / (3.7 + 1.3)) * 800) + 100;
		square->second.y = ((1 - ((square->second.y - 47.9) / (49.3 - 47.9))) * 800) + 100;
	}
	third = makecoord(rt, square->first.x, square->second.y);
	fourth = makecoord(rt, square->second.x, square->first.y);
	printdroite(rt, square->first, third, square->color);
	printdroite(rt, third, square->second, square->color);
	printdroite(rt, square->second, fourth, square->color);
	printdroite(rt, fourth, square->first, square->color);
}
void	bresenhamoneeight(t_rt *rt, t_coord one, t_coord two, t_color color)
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
		printpixelimg(rt, makecoord(rt, one.x, one.y), color);
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
void	bresenhamthreesix(t_rt *rt, t_coord one, t_coord two, t_color color)
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
		printpixelimg(rt, makecoord(rt, one.x, one.y), color);
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

void	bresenhamfourfive(t_rt *rt, t_coord one, t_coord two, t_color color)
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
		printpixelimg(rt, makecoord(rt, one.x, one.y), color);
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

void	bresenhamtwoseven(t_rt *rt, t_coord one, t_coord two, t_color color)
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
		printpixelimg(rt, makecoord(rt, one.x, one.y), color);
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

void	bresenham(t_rt *rt, t_coord one, t_coord two, t_color color)
{
	int	dx;
	int	dy;

	if (two.x - one.x < 0)
		swapcoord(&one, &two);
	dx = two.x - one.x;
	dy = two.y - one.y;
	if (dy != 0)
	{
		if (dy > 0)
		{
			if (dx >= dy)
				bresenhamfourfive(rt, one, two, color);
			else
				bresenhamoneeight(rt, one, two, color);
		}
		else
		{
			if (dx >= -dy)
				bresenhamthreesix(rt, one, two, color);
			else
				bresenhamtwoseven(rt, one, two, color);
		}
	}
	printpixelimg(rt, makecoord(rt, two.x, two.y), color);
}

void	swapy(t_coord *one, t_coord *two)
{
	float	mem;

	mem = one->y;
	one->y = two->y;
	two->y = mem;
}

void	swapx(t_coord *one, t_coord *two)
{
	float	mem;

	mem = one->x;
	one->x = two->x;
	two->x = mem;
}

void	printsamey(t_rt *rt, t_coord one, t_coord two, t_color color)
{	
	if (two.x > one.x)
		swapx(&one, &two);
	while (one.x >= two.x)
	{
		printpixelimg(rt, makecoord(rt, one.x, one.y), color);
		one.x--;
	}
}

void	printdiagonefour(t_rt *rt, t_coord one, t_coord two, t_color color)
{
	while (one.x != two.x)
	{
		printpixelimg(rt, makecoord(rt, one.x, one.y), color);
		one.x++;
		one.y++;
	}
	printpixelimg(rt, makecoord(rt, one.x, one.y), color);
}

void	printdiagtwothree(t_rt *rt, t_coord one, t_coord two, t_color color)
{
	while (one.x != two.x)
	{
		printpixelimg(rt, makecoord(rt, one.x, one.y), color);
		one.x++;
		one.y--;
	}
	printpixelimg(rt, makecoord(rt, one.x, one.y), color);
}

void	printdiag(t_rt *rt, t_coord one, t_coord two, t_color color)
{
	if (one.x - two.x == one.y - two.y)
	{
		if (two.x < one.x && two.y < one.y)
			swapcoord(&one, &two);
		printdiagonefour(rt, one, two, color);
	}
	else
	{
		if (one.x > two.x)
			swapcoord(&one, &two);
		printdiagtwothree(rt, one, two, color);
	}
}

void	printsamex(t_rt *rt, t_coord one, t_coord two, t_color color)
{
	if (one.x == two.x)
	{
		if (two.y > one.y)
			swapy(&one, &two);
		while (one.y >= two.y)
		{
			printpixelimg(rt, makecoord(rt, one.x, one.y), color);
			one.y--;
		}
	}
}

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
        printpixelimg(rt, makecoord(rt, x + x0, y + y0), color);  // Octant 1
        printpixelimg(rt, makecoord(rt, y + x0, x + y0), color);  // Octant 2
        printpixelimg(rt, makecoord(rt, -x + x0, y + y0), color); // Octant 4
        printpixelimg(rt, makecoord(rt, -y + x0, x + y0), color); // Octant 3
        printpixelimg(rt, makecoord(rt, -x + x0, -y + y0), color); // Octant 5
        printpixelimg(rt, makecoord(rt, -y + x0, -x + y0), color); // Octant 6
        printpixelimg(rt, makecoord(rt, x + x0, -y + y0), color);  // Octant 7
        printpixelimg(rt, makecoord(rt, y + x0, -x + y0), color);  // Octant 8
        y++;

        if (decisionOver2 <= 0) {
            decisionOver2 += 2 * y + 1;
        } else {
            x--;
            decisionOver2 += 2 * (y - x) + 1;
        }
    }
}

void	printLycee(t_rt *rt, t_lycee *sp)
{
	if (sp->coord.x != 0 && sp->coord.y != 0)
	drawCircle(rt, sp->coord.x, sp->coord.y, sp->rayon, sp->color);
}

void	printdroite(t_rt *rt, t_coord one, t_coord two, t_color color)
{
	if (one.x == two .x)
		printsamex(rt, one, two, color);
	else if (one.y == two.y)
		printsamey(rt, one, two, color);
	else if (ft_abs(one.x - two.x) == ft_abs(one.y - two.y))
		printdiag(rt, one, two, color);
	else
		bresenham(rt, one, two, color);
}

void	printobj(t_rt *rt, t_obj *obj)
{
	if (obj->type == SEG)
		printseg(rt, (t_seg *)obj->obj);
	if (obj->type == SQUARE)
		printSquare(rt, (t_square *)obj->obj);
	if (obj->type == LYCEE)
		printLycee(rt, (t_lycee *)obj->obj);
}

