#include "../include/rt.h"

int	getred(int rgb)
{
	return ((rgb >> 16) & 0xFF);
}

int	getgreen(int rgb)
{
	return ((rgb >> 8) & 0xFF);
}

int	getblue(int rgb)
{
	return (rgb & 0xFF);
}

t_lycee	*listToLycee(t_list *liste)
{
	t_obj	*obj;
	t_lycee *lycee;

	obj = (t_obj *)liste->content;
	lycee = (t_lycee *)obj->obj;
	return (lycee);
}

t_square	*listToSquare(t_list *liste)
{
	t_obj	*obj;
	t_square	*square;

	obj = (t_obj *)liste->content;
	square = (t_square *)obj->obj;
	return (square);
}

int	listToType(t_list *liste)
{
	t_obj	*obj;

	obj = liste->content;
	return (obj->type);
}

int	colorToInt(t_color *color)
{
	return (color->red << 16 | color->green << 8 | color->blue);
}

t_color	intToColor(int color)
{
	t_color	new;

	new.red = getred(color);
	new.blue = getblue(color);
	new.green = getgreen(color);
	return (new);
}
