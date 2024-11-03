#include "../include/rt.h"
#include <bits/types/cookie_io_functions_t.h>
#include <stdio.h>

t_coord	ft_makecoord(t_rt *rt, double x, double y)
{
	static t_coord	coord;

	coord.x = x;
	coord.y = y;
	return (coord);
}

int	ft_getred(int rgb)
{
	return ((rgb >> 16) & 0xFF);
}

int	ft_getgreen(int rgb)
{
	return ((rgb >> 8) & 0xFF);
}

int	ft_getblue(int rgb)
{
	return (rgb & 0xFF);
}

int	ft_regetcolorint(t_color *color)
{
	return (color->red << 16 | color->green << 8 | color->blue);
}

t_color	ft_getfromint(t_rt *rt, int color)
{
	t_color	*new;

	new = ft_malloc(sizeof(t_color), &rt->garbage);
	if (!new)
		ft_exit(rt, "malloc error\n");
	new->red = ft_getred(color);
	new->blue = ft_getblue(color);
	new->green = ft_getgreen(color);
	return (*new);
}

int	ft_quit(t_rt *rt)
{
	if (rt->image.origin != 0)
		mlx_destroy_image(rt->mlx_ptr, rt->image.origin);
	if (rt->win_ptr != 0)
		mlx_destroy_window(rt->mlx_ptr, rt->win_ptr);
	if (rt->mlx_ptr != 0)
		mlx_destroy_display(rt->mlx_ptr);
	free(rt->mlx_ptr);
	ft_exit(rt, 0);
	return (0);
}

void	ft_printpixelimg(t_rt *rt, t_coord print, t_color color)
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
	colorint = ft_regetcolorint(&color);
	*(int *)pixel = colorint;
}

void	ft_printseg(t_rt *rt, t_seg *seg)
{
	ft_printdroite(rt, (*seg).first, (*seg).second, (*seg).color);
}

void	ft_printSquare(t_rt *rt, t_square *square)
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
	third = ft_makecoord(rt, square->first.x, square->second.y);
	fourth = ft_makecoord(rt, square->second.x, square->first.y);
	ft_printdroite(rt, square->first, third, square->color);
	ft_printdroite(rt, third, square->second, square->color);
	ft_printdroite(rt, square->second, fourth, square->color);
	ft_printdroite(rt, fourth, square->first, square->color);
}


t_square	*ft_makenewsquare(t_rt *rt, t_coord coord1, t_coord coord2, t_color color)
{
	t_square	*square;

	square = ft_malloc(sizeof(t_square), &rt->garbage);
	if (!square)
		ft_exit(rt, "malloc error\n");
	square->first = coord1;
	square->second = coord2;
	square->color = color;
	return (square);
}

t_square *ft_makefirstsquare(t_rt *rt)
{
	t_coord	*coord1;
	t_coord	*coord2;

	t_square	*square;

	square = ft_malloc(sizeof(t_square), &rt->garbage);
	if (!square)
		ft_exit(rt, "malloc error\n");
	square->first = ft_makecoord(rt, rt->objxmax, rt->objymax);
	square->second = ft_makecoord(rt, rt->objxmin, rt->objymin);
	square->color = rt->color;
	return (square);
}

t_coord	ft_squaresplit(t_rt *rt, t_square *square)
{
	double	x;
	double	y;

	x = (-square->second.x + square->first.x) / 2 + square->second.x;
	y = (-square->second.y + square->first.y) / 2 + square->second.y;
	return (ft_makecoord(rt, x, y));
}

t_line	*ft_findsplitsquare(t_rt *rt, t_pos *obj, t_square *square, int depth)
{
	t_line	*line;

	line = ft_malloc(sizeof(t_line), &rt->garbage);
	if (!line)
		ft_exit(rt, "malloc error\n");
	if (depth == 0)
	{
		line->coord = ft_squaresplit(rt, square);
		line->ori = ft_makecoord(rt, 0, 1);
		line->color = rt->color;
	}
	if (depth == 1)
	{
		line->coord = ft_squaresplit(rt, square);
		line->ori = ft_makecoord(rt, 1, 0);
		line->color = rt->color;
	}
	return (line);
}

void	ft_printobj(t_rt *rt, t_obj *obj)
{
	if (obj->type == SEG)
		ft_printseg(rt, (t_seg *)obj->obj);
	if (obj->type == SQUARE)
		ft_printSquare(rt, (t_square *)obj->obj);
	if (obj->type == LYCEE)
		ft_printLycee(rt, (t_lycee *)obj->obj);
}

void	printObjListName(t_rt *rt, t_pos *print)
{
	t_list	*liste;
	int		mem;
	static int lol = 0;

	if (!print || print->size == 0) {
		return;
	}
	mem = 0;
	liste = print->start;
	while (liste != print->start || mem++ == 0)
	{
		// if (listToLycee(liste)->value > lol) {
			printf("%s ", listToLycee(liste)->name);
			// printf("%d ", print->size);
			// lol = test;
		// }
		liste = liste->next;
	}
	// printf("\nsize max: %d\n", lol);
	// printf("\nnode number: %d\n", lol2);
	// printf("\n: %d\n", lol3);
	printf("\n");
}

void	ft_printobjlist(t_rt *rt, t_pos *print)
{
	t_list	*liste;
	int		mem;

	if (!print || print->size == 0)
		return;
	mem = 0;
	liste = print->start;
	while (liste != print->start || mem++ == 0)
	{
		ft_printobj(rt, (t_obj *)liste->content);
		liste = liste->next;
	}
}

t_square	*ft_splitsquaregauche(t_rt *rt, t_square *square, t_line *line, int depth)
{
	t_coord	coord1;
	t_coord	coord2;

	if (depth == 0)
	{
		coord1 = ft_makecoord(rt, square->first.x, square->first.y);
		coord2 = ft_makecoord(rt, line->coord.x, square->second.y);
	}
	if (depth == 1)
	{
		coord1 = ft_makecoord(rt, square->first.x, square->first.y);
		coord2 = ft_makecoord(rt, square->second.x, line->coord.y);
	}
	return (ft_makenewsquare(rt, coord1, coord2, rt->color));
}

t_square	*ft_splitsquaredroite(t_rt *rt, t_square *square, t_line *line, int depth)
{
	t_coord	coord1;
	t_coord	coord2;

	if (depth == 0)
	{
		coord1 = ft_makecoord(rt, line->coord.x, square->first.y);
		coord2 = ft_makecoord(rt, square->second.x, square->second.y);
	}
	if (depth == 1)
	{
		coord1 = ft_makecoord(rt, square->first.x, line->coord.y);
		coord2 = ft_makecoord(rt, square->second.x, square->second.y);
	}
	return (ft_makenewsquare(rt, coord1, coord2, rt->color));
}

t_pos	*objRight(t_rt *rt, t_line *line, t_pos *obj, int depth)
{
	t_pos	*new;
	t_list	*mem;
	int		lol;

	lol = 0;
	new = ft_setpos(&rt->garbage);
	if (!new)
		ft_exit(rt, "malloc error\n");
	mem = obj->start;
	if (!mem)
		return (new);
	while (mem != obj->start || !lol++)
	{
		if (((t_obj *)mem->content)->xmin < line->coord.x && depth == 0)
		{
			listToLycee(mem)->color.red += 50;
			mem = mem->next;
			ft_lstnew(mem->back->content ,new, &rt->garbage);
		}
		else if (((t_obj *)mem->content)->ymin < line->coord.y && depth == 1)
		{
			listToLycee(mem)->color.red += 50;
			mem = mem->next;
			ft_lstnew(mem->back->content ,new, &rt->garbage);
		}
		else
			mem = mem->next;
	}
	return (new);
}


t_pos	*objLeft(t_rt *rt, t_line *line, t_pos *obj, int depth)
{
	t_pos	*new;
	t_list	*mem;
	int		lol;

	lol = 0;
	new = ft_setpos(&rt->garbage);
	if (!new)
		ft_exit(rt, "malloc error\n");
	mem = obj->start;
	if (!mem)
		return (new);
	while (mem != obj->start || !lol++)
	{
		if (((t_obj *)mem->content)->xmax > line->coord.x && depth == 0)
		{
			listToLycee(mem)->color.blue += 50;
			mem = mem->next;
			ft_lstnew(mem->back->content ,new, &rt->garbage);
		}
		else if (((t_obj *)mem->content)->ymax > line->coord.y && depth == 1)
		{
			listToLycee(mem)->color.blue += 50;
			mem = mem->next;
			ft_lstnew(mem->back->content ,new, &rt->garbage);
		}
		else
			mem = mem->next;
	}
	return (new);
}

// void	ft_clearobjlist(t_pl *pl, t_pos *obj, int depth)
// {
// 	t_list	*mem;
// 	int		lol;
//
// 	lol = 0;
// 	mem = obj->start;
// 	if (!mem)
// 		return ;
// 	while (*mem->pos->size != 0 && (mem != obj->start || !lol++))
// 	{
// 		if ((((t_obj *)mem->content)->xmax != pl->coord->x || ((t_obj *)mem->content)->xmin != pl->coord->x) && depth == 0)
// 		{
// 			lol--;
// 			mem = mem->next;
// 			ft_lstdelone(mem->back ,0);
// 		}
// 		else if ((((t_obj *)mem->content)->ymax != pl->coord->y || ((t_obj *)mem->content)->ymin != pl->coord->y) && depth == 1)
// 		{
// 			lol--;
// 			mem = mem->next;
// 			ft_lstdelone(mem->back ,0);
// 		}
// 		else if ((((t_obj *)mem->content)->zmax != pl->coord->z || ((t_obj *)mem->content)->zmin != pl->coord->z) && depth == 2)
// 		{
// 			lol--;
// 			mem = mem->next;
// 			ft_lstdelone(mem->back ,0);
// 		}
// 		else
// 			mem = mem->next;
// 	}
// }

t_pos	*ft_lstdup(t_pos *pos, t_pos *garbage)
{
	t_pos	*new;
	t_list	*liste;
	int	i;

	i = 0;
	liste = pos->start;
	new = ft_setpos(garbage);
	while (i < pos->size)
	{
		ft_lstnew(liste->content, new, garbage);
		liste = liste->next;
		i++;
	}
	return (new);
}


t_bt	*ft_newleaf(t_rt *rt, t_pos *obj)
{
	t_bt *new;

	new = ft_malloc(sizeof(t_bt), &rt->garbage);
	if (!new)
		ft_exit(rt, "malloc error\n");
	new->obj = obj;
	new->right = 0;
	new->racine = 0;
	new->left = 0;
	new->split = 0;
	return (new);
}

t_bt	*ft_newnoeu(t_rt *rt, t_bt *right, t_bt *left, t_line *split)
{
	t_bt	*new;

	new = ft_newleaf(rt, 0);
	if (right)
		right->racine = new;
	if (left)
		left->racine = new;
	new->left = left;
	new->right = right;
	new->racine = 0;
	new->split = split;
	return (new);
}

void	printLineInSquare(t_rt *rt, t_line *line, t_square *square)
{
	t_coord	first;
	t_coord	second;

	first = ft_makecoord(rt, line->coord.x + rt->xsize * line->ori.x, line->coord.y + rt->ysize * line->ori.y);
	if (first.x > square->first.x)
		first.x = square->first.x;
	if (first.y > square->first.y)
		first.y = square->first.y;
	second = ft_makecoord(rt, line->coord.x + -(rt->xsize * line->ori.x), line->coord.y + -(rt->ysize * line->ori.y));
	if (second.x < square->second.x)
		second.x = square->second.x;
	if (second.y < square->second.y)
		second.y = square->second.y;
	ft_printdroite(rt, second, first, line->color);
	line->color.red = line->color.red + 30;
	line->color.green = line->color.green + 30;
	first = ft_makecoord(rt, line->coord.x + 10 * line->ori.y, line->coord.y + 10 * line->ori.x);
	ft_printdroite(rt, line->coord, first, line->color);
}

t_bt	*treeConstruct(t_rt *rt, t_pos *obj, t_square *square, int depth, int history[3])
{
	t_line	*line;
	t_square	*squareRight;
	t_square	*squareLeft;
	t_pos	*objListRight;
	t_pos	*objListLeft;

	if (obj->size == 0)
		return 0;
	if (depth >= 30 || (obj->size == history[0] && obj->size == history[1] && obj->size == history[2]))
		return (ft_newleaf(rt, obj));
	line = ft_findsplitsquare(rt, obj, square, depth % 2);
	// printLineInSquare(rt, line, square);
	squareRight = ft_splitsquaredroite(rt, square, line, depth % 2);
	squareLeft = ft_splitsquaregauche(rt, square, line, depth % 2);
	history[0] = history[1];
	history[1] = history[2];
	history[2] = obj->size;
	objListLeft = objLeft(rt, line, obj, depth % 2);
	objListRight = objRight(rt, line, obj, depth % 2);
	return (ft_newnoeu(rt, treeConstruct(rt, objListRight, squareRight, depth + 1, history), treeConstruct(rt, objListLeft, squareLeft, depth + 1, history), line));
}

void	printList(t_rt *rt, t_pos *pos) {
	t_list	*liste;
	int		mem;
	static int		lol = 0;

	if (!pos || pos->size == 0) {
		return;
	}
	mem = 0;
	liste = pos->start;
	while (liste != pos->start || mem++ == 0)
	{
			// printf("%s\n", listToLycee(liste)->name);
		if (listToLycee(liste)->value >= lol) {
			lol = listToLycee(liste)->value;
			printf("act: %s\n", listToLycee(liste)->name);
			printf("value: %f\n", listToLycee(liste)->value);
		}

		liste = liste->next;
	}
}
double maxToParse = 0;

void	addValueOne(t_rt *rt, t_pos *obj, t_lycee *add) {
	// t_list	*liste;
	// int		mem;
	// int	toAdd = 0;
	//
	if (!obj || obj->size == 0) {
		return;
	}
	static int lol = 0;
	// mem = 0;
	// liste = obj->start;
	// while (liste != obj->start || mem++ == 0)
	// {
	// 	if (add->name != listToLycee(liste)->name) {
	// 		toAdd++;
	// 	// printf("yessssssss %s %f\n",add->name, add->value);
	// 	}
	// 	liste = liste->next;
	// }
	// if (toAdd != obj->size - 1)
		// printf("%d %d\n", toAdd, obj->size - 1);
	if (obj->size - 1 > add->value)
		add->value = obj->size - 1;
	if (add->value > maxToParse) {
		maxToParse = add->value;
		// printf("%f %s\n", add->value, add->name);
	}

	// if (add->value == 41) {
		// ft_printLycee(rt, add);
	// }
	// printList(rt, obj);
}

void	addValueAll(t_rt *rt, t_pos *obj) {
	t_list	*liste;
	int		mem;

	if (!obj || obj->size == 0) {
		return;
	}
	mem = 0;
	liste = obj->start;
	while (liste != obj->start || mem++ == 0)
	{
		addValueOne(rt, obj, listToLycee(liste));
		liste = liste->next;
	}
}


void	exploreTree(t_rt *rt, t_bt *tree) {
	static int lol = 0;
	if (tree->left) {
		exploreTree(rt, tree->left);
	// printObjListName(rt, tree->obj);
	}
	if (tree->right) {
		exploreTree(rt, tree->right);
	// printObjListName(rt, tree->obj);
	}
	if (tree->obj && tree->obj->size != 0) {
		addValueAll(rt, tree->obj);
	// printf("node: %i\n", lol);
	// lol++;
	// printObjListName(rt, tree->obj);
	}


}

void	exploreTree2(t_rt *rt, t_bt *tree) {
	if (tree->left)
		exploreTree2(rt, tree->left);
	if (tree->right)
		exploreTree2(rt, tree->right);
	// printList(rt, tree->obj);
	// printObjListName(rt, tree->obj);
	// ft_printobjlist(rt, tree->obj);
	// if (tree->obj && tree->obj->size != 0) {
	// }


}

t_bt *searchCoordInTree(t_rt *rt, t_bt *tree, t_coord coord) {
	if (tree->obj && tree->obj->size != 0) {
		return (tree);
	}
	if (tree->split->ori.x == 0) {
		if (tree->split->coord.x <= coord.x) {
			return (searchCoordInTree(rt, tree->left, coord));
		}
		else {
			return (searchCoordInTree(rt, tree->right, coord));
		}
	}
	else {
		if (tree->split->coord.y <= coord.y) {
			return (searchCoordInTree(rt, tree->left, coord));
		}
		else {
			return (searchCoordInTree(rt, tree->right, coord));
		}
	}
	return 0;
}

void	ft_construcbtree(t_rt *rt)
{
	t_square	*square;
	t_pos	*start;
	t_bt	*tree;
	t_bt	*in;
	int	history[3];

	// printf("%d\n", rt->obj.size);
	// start = ft_lstdup(&rt->obj, &rt->garbage);
	square = ft_makefirstsquare(rt);
	history[0] = -1;
	history[1] = -1;
	history[2] = -1;
	rt->tree = treeConstruct(rt, &rt->obj, square, 0, history);
	exploreTree(rt, rt->tree);
	// exploreTree2(rt, tree);
	// printList(rt, &rt->obj);
	// printf("%d\n", rt->obj.size);
	// in = searchCoordInTree(rt, tree, ft_makecoord(rt, 200, 800));
	// printf("alors: %p\n", in);
	// printObjListName(rt, in->obj);

}

void	ft_clearimg(t_rt *rt)
{
	int	x;
	int	y;
	int	bit;
	int	mem;
	int	mem2;
	char	*pixel;

	x = 0;
	y = 0;
	mem = rt->image.size_line;
	bit = rt->image.bits_per_pixel / 8;
	while (y < rt->ysize)
	{
		while (x < rt->xsize)
		{
			mem2 = y * mem + x * bit;
			if (rt->image.imgaddress[mem2] != 0)
			{
				pixel = rt->image.imgaddress + mem2;
				*(int *)pixel = 0;
			}
			x++;
		}
		y++;
		x = 0;
	}
}

void	ft_inibtruert(t_rt *rt)
{
	rt->mlx_ptr = mlx_init();
	if (rt->mlx_ptr == 0)
		ft_exit(rt, "Error");
	rt->win_ptr = mlx_new_window(rt->mlx_ptr, rt->xsize, rt->ysize, "rt");
	if (rt->win_ptr == 0)
		ft_quit(rt);
	rt->image.origin = mlx_new_image(rt->mlx_ptr, rt->xsize, rt->ysize);
	if (rt->image.origin == 0)
		ft_quit(rt);
	rt->image.imgaddress = mlx_get_data_addr(rt->image.origin,
			&rt->image.bits_per_pixel,
			&rt->image.size_line, &rt->image.endian);
}

t_coord	ft_atoicoord(t_rt *rt, char *str)
{
	t_coord	coord;
	int		i;

	i = 0;
	coord.x = ft_atoi(&str[i]);
	while (str[i] && str[i] != ',')
		i++;
	if (str[i] == ',')
		i++;
	coord.y = ft_atoi(&str[i]);
	while (str[i] && str[i] != ',')
		i++;
	return (coord);
}

void	ft_calcLycee(t_obj *objet)
{
	t_lycee	*lycee;

	lycee = (t_lycee *)objet->obj;
	objet->xmin = lycee->coord.x - lycee->rayon;
	objet->xmax = lycee->coord.x + lycee->rayon;
	objet->ymin = lycee->coord.y - lycee->rayon;
	objet->ymax = lycee->coord.y + lycee->rayon;
}

void	ft_calcsquare(t_obj *objet)
{
	t_square	*square;

	square = (t_square *)objet->obj;
	objet->xmin = ft_min(square->first.x, square->second.x);
	objet->ymin = ft_min(square->first.y, square->second.y);
	objet->xmax = ft_max(square->first.x, square->second.x);
	objet->ymax = ft_max(square->first.y, square->second.y);
}


void	ft_calccoordobjrt(t_rt *rt, t_obj *obj)
{
	if (obj->xmin < rt->objxmin)
		rt->objxmin = obj->xmin;
	if (obj->ymin < rt->objymin)
		rt->objymin = obj->ymin;
	if (obj->ymax > rt->objymax)
		rt->objymax = obj->ymax;
	if (obj->xmax > rt->objxmax)
		rt->objxmax = obj->xmax;
}

// void	ft_recalc(t_rt *rt)
// {
// 	t_list	*liste;
// 	int		mem;
//
// 	rt->objxmin = 200000000;
// 	rt->objxmax = -200000000;
// 	rt->objymin = 200000000;
// 	rt->objymax = -200000000;
// 	rt->objzmin = 200000000;
// 	rt->objzmax = -200000000;
// 	mem = 0;
// 	liste = rt->obj->start;
// 	while (liste != rt->obj->start || mem++ == 0)
// 	{
// 		ft_calccoordobjrt(rt, (t_obj *)liste->content);
// 		liste = liste->next;
// 	}
// }
//
void	ft_calcobj(t_rt *rt, t_obj *objet)
{
	if (objet->type == LYCEE)
		ft_calcLycee(objet);
	else if (objet->type == SQUARE)
		ft_calcsquare(objet);
	ft_calccoordobjrt(rt, objet);
}
//
// void	ft_moveonecoord(void *obj, t_coord *coord)
// {
// 	t_sp	*sp;
//
// 	sp = (t_sp *)obj;
// 	if (coord->x != 0)
// 		sp->coord->x = sp->coord->x + coord->x;
// 	if (coord->y != 0)
// 		sp->coord->y = sp->coord->y + coord->y;
// 	if (coord->z != 0)
// 		sp->coord->z = sp->coord->z + coord->z;
// }
//
// int		ft_isonecoordex(t_rt *rt, void *obj)
// {
// 	t_coord	*coord;
//
// 	coord = ((t_sp *)obj)->coord;
// 	if (coord->x == rt->objxmin || coord->x == rt->objxmax)
// 		return (1);
// 	if (coord->y == rt->objymin || coord->y == rt->objymax)
// 		return (1);
// 	if (coord->z == rt->objzmin || coord->z == rt->objzmax)
// 		return (1);
// 	return (0);
// }
//
// void	ft_movecam(t_rt *rt, t_coord *dep)
// {
// 	*rt->cam.coord = *rt->cam.coord + *dep;
// }
//
// void	ft_moveobj(t_rt *rt, t_obj *obj, t_coord *dep)
// {
// 	int	mem;
//
// 	if (obj->type == C || obj->type == SP)
// 	{
// 		mem = ft_isonecoordex(rt, obj->obj);
// 		ft_moveonecoord((t_sp *)obj->obj, dep);
// 		ft_calcobj(rt, obj);
// 		if (mem)
// 			ft_recalc(rt);
// 	}
// }
//
// */
// float	ft_normcarre(t_coord one)
// {
// 	return (one.x * one.x + one.y * one.y + one.z * one.z);
// }
//
// float	ft_normcarree(t_coord one)
// {
// 	return (one.x * one.x + one.y * one.y + one.z * one.z);
// }
//
// float	ft_scalaire(t_coord one, t_coord two)
// {
// 	return (one.x * two.x + one.y * two.y + one.z * two.z);
// }
//
// void	ft_norm(t_coord *one)
// {
// 	float	norm;
//
// 	norm = sqrt(ft_normcarre(*one));
// 	*one = *one / norm;
// }
//
// float	ft_maxchar(float one)
// {
// 	if (one > 255)
// 		return (255);
// 	return (one);
// }
//
// float	ft_minchar(float one)
// {
// 	if (one < 20)
// 		return (20);
// 	return (one);
// }
//
// typedef struct	s_temp
// {
// 	t_coord	normal;
// 	t_coord	coordinter;
// 	
// }	t_temp;
//
// int ft_lcolor()
// {
// //	unsigned mask1 = 255 << 16 | 255 << 8 | 255;
// 	unsigned mask2 = 255 << 24 | 255 << 8 | 255;
// //	unsigned mask3 = 255 << 24 | 255 << 16 | 255;
// //	unsigned mask4 = 255 << 24 | 255 << 16 | 255 << 8;
//
// 	int	c;
// 	unsigned color;
//
// 	color = mask2 | 0 << 16;
// 	c = 0 << 24 | 255 << 16 | 0 << 8 | 0;
// 	c = color & c;
// 	return (c);
// }
// /*
// 	
// */
// float	ft_intersectsp(t_rt *rt ,t_ray *rayon, t_sp *sp)
// {
// 	float	a;
// 	float	b;
// 	float	c;
// 	float	delta;
// 	float	sol1;
//
//
// 	a = 1;
// 	b = 2 * ft_scalaire((*rayon).ori, rt->origin - (*sp).coord);
// 	c = ft_normcarre((*sp).coord) - sp->rayon * sp->rayon;
// 	delta = b * b - 4 * a * c;
// 	if (delta < 0)
// 		return (0);
// 	sol1 = (-b -(sqrt(delta))) / (2 * a);
// 	if (sol1<=0)
// 		sol1 = (-b + (sqrt(delta))) / (2 * a);
// 	return (sol1);
// }
//
// t_color	*ft_coloralbedo(t_rt *rt, float intensity, t_sp *obj)
// {
// 	t_color	color;
// 	t_color	*new;
//
// 	if (!intensity)
// 		return (0);
// 	new = ft_malloc(sizeof(t_color), rt->garbage);
// 	if (!new)
// 		ft_exit(rt, "malloc error\n");
// 	color = obj->color;
// 	new->green = (intensity * color.green / 255);
// 	new->blue = (intensity * color.blue / 255);
// 	new->red = (intensity * color.red / 255);
// 	return (new);
//
// }
// /*
// P = coordinter
// */
// float	ft_findsol(t_rt *rt, t_ray *rayon, t_obj *obj);
// t_obj	*ft_findobj(t_rt *rt, t_ray *rayon, float *sol);
//
// int	ft_wasinshaddow(t_rt *rt, t_coord *obj)
// {
// 	t_ray	rayon;
// 	t_obj	*obja;
// 	float	sol;
// 	t_coord	ori;
// 	t_coord *light;
//
// 	rayon.coord = *obj;
// 	light = &rt->light.coord;
// 	ori.x = light->x - obj->x;
// 	ori.y = light->y - obj->y;
// 	ori.z = light->z - obj->z;
// 	rayon.ori = ori;
// 	obja = ft_findobj(rt, &rayon, &sol);
// 	if (!obja)
// 		return (0);
// 	if (sol < 1 && sol > 0)
// 		return (1);
// 	return (0);
// }
//
// float	ft_findintensity(t_rt *rt, t_ray *rayon, float sol, t_sp *obj)
// {
// 	float	intensity;
// 	t_coord	normal;
// 	t_coord	coordinter;
//
// 	if (sol == 0)
// 		return (0);
// 	coordinter = (*rayon).coord + (sol * (*rayon).ori);
// 	if (ft_wasinshaddow(rt, &coordinter) == 1)
// 		return (50);
// 	normal = coordinter - (*obj).coord;
// 	ft_norm(&normal);
// 	ft_norm(&rt->light.coord);
// 	intensity = rt->light.intensiter * (ft_maxchar(ft_scalaire(rt->light.coord, normal) / (ft_normcarree(rt->light.coord - coordinter)))) + 150;
// 	intensity = ft_maxchar(intensity);
// 	intensity = ft_minchar(intensity);
// 	return (intensity);
// }
//
// float	ft_findsol(t_rt *rt, t_ray *rayon, t_obj *obj)
// {
// 	float	sol;
//
// 	sol = 0;
// 	if (obj->type == SP)
// 		sol = ft_intersectsp(rt, rayon, obj->obj);
// 	return (sol);
// }
//
// t_obj	*ft_findobj(t_rt *rt, t_ray *rayon, float *sol)
// {
// 	t_list	*objact;
// 	t_list	*toprint;
// 	float	mem;
// 	
// 	toprint = 0;
// 	objact = rt->obj->start;
// 	*sol = ft_findsol(rt, rayon, objact->content);
// 	if (*sol < 0)
// 		*sol = 0;
// 	toprint = objact;
// 	objact = objact->next;
// 	while (objact != rt->obj->start)
// 	{
// 		mem = ft_findsol(rt, rayon, objact->content);
// 		if (!*sol || (mem < *sol && mem > 0))
// 		{
// 			*sol = mem;
// 			toprint = objact;
// 		}
// 		objact = objact->next;
// 	}
// 	if (*sol <= 0)
// 		return (0);
// 	return (toprint->content);
// }
//
// t_color	ft_getblack()
// {
// 	static t_color	black;
//
// 	black.red = 0;
// 	black.green = 0;
// 	black.blue = 0;
// 	return (black);
// }
//
t_color	ft_findcolor(t_rt *rt)
{
	t_color	color;

	color.red = 0;
	color.green = 0;
	color.blue = 100;
	return (color);
}

int	coordInCircle(t_coord coord, t_lycee *lycee) {
	double distance = sqrt(pow(coord.x - lycee->coord.x, 2) + pow(coord.y - lycee->coord.y, 2));
	if (distance <= lycee->rayon) {
		return 1;
	}
	return 0;
}

void	calcInside(t_rt *rt, t_lycee *lyc, t_pos *obj) {
	t_list	*liste;
	t_bt	*find;
	int		mem;
	int add =0;
	static int lol = 0;

	if (!obj || obj->size == 0) {
		return;
	}
	mem = 0;
	liste = obj->start;
	while (liste != obj->start || mem++ == 0)
	{
		if (listToLycee(liste)->name != lyc->name) {
			if (coordInCircle(lyc->coord, listToLycee(liste)))
				add++;

		}
		liste = liste->next;
	}
	if (add >= lol) {
		lol = add;
		printf("lol%d\n", add);
		printf("name: %s\n", lyc->name);

	}

}

void	printListMax(t_rt *rt, t_pos *pos) {
	t_list	*liste;
	t_bt	*find;
	int		mem;

	if (!pos || pos->size == 0) {
		return;
	}
	mem = 0;
	liste = pos->start;
	printf("66666666666666666qqqqqqqqqqq\n");
	while (liste != pos->start || mem++ == 0)
	{
			// printf("%s\n", listToLycee(liste)->name);
		if (listToLycee(liste)->value >= maxToParse) {
			find = searchCoordInTree(rt, rt->tree, listToLycee(liste)->coord);
			if (find) {
				calcInside(rt, listToLycee(liste), find->obj);
			}
		}
		liste = liste->next;
	}
	printf("555555555555555555555qqqqqqqqq\n");
}

void	findCoordMax(t_rt *rt) {
	printf("7777777qqqqqqqqqqq\n");
	printListMax(rt, &rt->obj);
	printf("88888888qqqqqqqqqq\n");
}

void	ft_printfirst(t_rt *rt)
{
	printf("qqqqqqqqqqqqqqqqqq\n");
	ft_clearimg(rt);
	ft_construcbtree(rt);
	printf("qqqqqqqqqqqqqqqqqq\n");
	findCoordMax(rt);
	printf("qqqqqqqqqqqqqqqqqq\n");
	ft_printobjlist(rt, &rt->obj);
	printf("qqqqqqqqqqqqqqqqqq\n");
	// ft_firsbtracing(rt);
	
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->image.origin, 0, 0);
}

int	ft_key_hook(int keycode, t_rt *rt)
{
	if (keycode == 65307)
		ft_quit(rt);
	ft_clearimg(rt);
	ft_printfirst(rt);
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->image.origin, 0, 0);
	return (keycode);
}

void	*ft_makeobj(t_rt *rt, void *obj, int type)
{
	t_obj	*objet;

	objet = ft_malloc(sizeof(t_obj), &rt->garbage);
	if (!obj)
		ft_exit(rt, "malloc error\n");
	objet->type = type;
	objet->obj = obj;
	ft_calcobj(rt, objet);
	return (objet);
}

// /*
// void	*ft_makeseg(t_rt *rt, char *str)
// {
// 	t_seg	*seg;
// 	int		i;
//
// 	i = 0;
// 	seg = ft_malloc(sizeof(t_seg), rt->garbage);
// 	if (!seg)
// 		ft_exit(rt, "malloc error\n");
// 	while (str[i] == ' ')
// 		i++;
// 	seg->first = ft_atoicoord(rt, &str[i]);
// 	while (str[i] && str[i] != ' ')
// 		i++;
// 	while (str[i] == ' ')
// 		i++;
// 	seg->second = ft_atoicoord(rt, &str[i]);
// 	while (str[i] && str[i] != ' ')
// 		i++;
// 	while (str[i] == ' ')
// 		i++;
// 	seg->color = ft_getfromint(rt, ft_atoi(&str[i]));
// 	return (ft_makeobj(rt, seg, SEG));
// }
//
// void	*ft_makesquare(t_rt *rt, char *str)
// {
// 	t_square	*square;
// 	int		i;
//
// 	i = 0;
// 	square = ft_malloc(sizeof(t_square), rt->garbage);
// 	if (!square)
// 		ft_exit(rt, "malloc error\n");
// 	while (str[i] == ' ')
// 		i++;
// 	square->first = ft_atoicoord(rt, &str[i]);
// 	while (str[i] && str[i] != ' ')
// 		i++;
// 	while (str[i] == ' ')
// 		i++;
// 	square->second = ft_atoicoord(rt, &str[i]);
// 	while (str[i] && str[i] != ' ')
// 		i++;
// 	while (str[i] == ' ')
// 		i++;
// 	square->color = ft_getfromint(rt, ft_atoi(&str[i]));
// 	return (ft_makeobj(rt, square, square));
// }
// */
// void	*ft_makesp(t_rt *rt, char *str)
// {
// 	t_sp	*sp;
// 	int		i;
//
// 	i = 0;
// 	sp = ft_malloc(sizeof(t_sp), rt->garbage);
// 	if (!sp)
// 		ft_exit(rt, "malloc error\n");
// 	while (str[i] == ' ')
// 		i++;
// 	sp->coord = ft_atoicoord(rt, &str[i]);
// 	while (str[i] && str[i] != ' ')
// 		i++;
// 	while (str[i] == ' ')
// 		i++;
// 	sp->rayon = ft_atoi(&str[i]);
// 	while (str[i] && str[i] != ' ')
// 		i++;
// 	while (str[i] == ' ')
// 		i++;
// 	sp->color = ft_getfromint(rt, ft_atoi(&str[i]));
// 	return (ft_makeobj(rt, sp, SP));
// }


int	ft_strstr(const char *big, const char *libtle) {
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;

	int bigLen = ft_strlen(big);
	int libtleLen = ft_strlen(libtle);
	if (libtle == 0 || big == 0) {
		return (-1);
	}
	while (big[i]) {
		j = 0;
		while (libtle[j] == big[i + j])
		{
			if (libtle[j + 1] == 0)
				return (i);
			j++;
		}
		i++;
	}
	return (-1);
}

char *searchJsonValue(t_rt *rt, char *str, char *toSearch) {
	int	start;
	int end;


	start = ft_strstr(str, toSearch);
	start = start + ft_strlen(toSearch) + 2;
	if (str[start] == '"')
		start++;
	end = ft_strstr(&str[start], "\"");
	if (end == -1) {
		end = ft_strlen(str) - 1;
	}
	end += start;
	return (ft_substr(str, start, end - start, &rt->garbage));
}


void	*ft_makeLycee(t_rt *rt, char *str)
{
	t_lycee	*new;
	int		i;
	char *end;

	new = ft_malloc(sizeof(t_lycee), &rt->garbage);
	if (!new)
		ft_exit(rt, "malloc error\n");
	new->coord.x = strtod(searchJsonValue(rt, str, "Longitude"), &end);
	new->coord.y = strtod(searchJsonValue(rt, str, "Latitude"), &end);

	if (TEST == 3) {
		if (new->coord.x < 1.3 || new->coord.x > 3.7 || new->coord.y < 47.9 || new->coord.y > 49.3)
			return 0;
	}
	else if (TEST != 2) {
		if (new->coord.x < -5.15 || new->coord.x > 9.56 || new->coord.y < 41.31 || new->coord.y > 51.1)
			return 0;
	}
	new->name = searchJsonValue(rt, str, "Nom_etablissement");
	if (TEST == 0)
		new->rayon = 0.1;
	if (TEST == 1)
		new->rayon = 0.01;
	if (TEST == 2)
		new->rayon = 20;
	if (TEST == 3)
		new->rayon = 0.01;
	new->color = ft_getfromint(rt, 900);
	new->value = 0;
	// printf("%s\n", str);
	t_obj *ret = ft_makeobj(rt, new, LYCEE);
	return (ret);
}

void	ft_parse(t_rt *rt, char	*in)
{
	int	i = 0;
	t_obj *new;
	i = ft_strstr(in, "Nom_etablissement");
	if (i != -1) {
		new = ft_makeLycee(rt, in);
		if (new)
		ft_lstnew(new, &rt->obj, &rt->garbage);
	}


		
//		if (in[i][0] == 's' && in[i][1] == 'e' && in[i][2] == 'g')
//			ft_lstnew(ft_makeseg(rt, &in[i][3]), rt->obj, rt->garbage);
//		if (in[i][0] == 'r' && in[i][1] == 'e' && in[i][2] == 'c')
//			ft_lstnew(ft_makesquare(rt, &in[i][3]), rt->obj, rt->garbage);
		// if (in[i][0] == 's' && in[i][1] == 'p')
			// ft_lstnew(ft_makesp(rt, &in[i][2]), rt->obj, rt->garbage);
//		if (in[i][0] == 'p' && in[i][1] == 'l')
//			ft_lstnew(ft_makepl(rt, &in[i][2]), rt->obj, rt->garbage);
		// if (in[i][0] == 'C')
			// ft_makecam(rt, &in[i][1]);
		// if (in[i][0] == 'L')
			// ft_makelight(rt, &in[i][1]);
}

void	ft_open(t_rt *rt)
{
	char	*temp;
	char	*ret;
	int		fd;

	ret = ft_strdup("", &rt->garbage);
	if (ret == 0)
		ft_exit(rt, "ERROR");
	if (TEST == 0)
		fd = open("lycee.json", O_RDONLY);
	if (TEST == 1)
		fd = open("lycee.json", O_RDONLY);
	if (TEST == 2)
		fd = open("test2.json", O_RDONLY);
	if (TEST == 3)
		fd = open("lycee.json", O_RDONLY);
	if (fd == -1)
		ft_exit(rt, "Error");
	int i = 0;
	while (1)
	{
		temp = get_next_line(fd, &rt->garbage);
		if (temp == 0)
		{
			close(fd);
			return ;
		}
		ft_parse(rt, temp);
	}
}

void	ft_rtcolor(t_rt *rt)
{
	rt->color = ft_getfromint(rt, 777777);
}

void	ft_initrt(t_rt *rt)
{
	t_pos	*garbage;

	rt->garbage.start = 0;
	rt->garbage.end = 0;
	rt->garbage.size = 0;
	rt->obj.start = 0;
	rt->obj.end = 0;
	rt->obj.size = 0;
	ft_rtcolor(rt);
	rt->win_ptr = 0;
	rt->mlx_ptr = 0;
	rt->objxmin = 200000000;
	rt->objxmax = -200000000;
	rt->objymin = 200000000;
	rt->objymax = -200000000;
	rt->xsize = 1000;
	rt->ysize = 1000;
	rt->origin = ft_makecoord(rt, 0, 0);
	rt->image.origin = 0;
	ft_open(rt);
}

void *ft_makeTout(t_rt *rt, char *str) {
    t_lycee *new;
    char *end;

    new = ft_malloc(sizeof(t_lycee), &rt->garbage);
    if (!new)
        ft_exit(rt, "malloc error\n");

    new->coord.x = strtod(searchJsonValue(rt, str, "longitude"), &end);
    new->coord.y = strtod(searchJsonValue(rt, str, "latitude"), &end);

    if (TEST == 3) {
        if (new->coord.x < 1.3 || new->coord.x > 3.7 || new->coord.y < 47.9 || new->coord.y > 49.3)
            return 0;
    } else if (TEST != 2) {
        if (new->coord.x < -5.15 || new->coord.x > 9.56 || new->coord.y < 41.31 || new->coord.y > 51.1)
            return 0;
    }
   new->type = searchJsonValue(rt, str, "type");

    if (TEST == 0)
        new->rayon = 0.1;
    else if (TEST == 1)
        new->rayon = 0.01;
    else if (TEST == 2)
        new->rayon = 20;
    else if (TEST == 3)
        new->rayon = 0.01;

    new->color = ft_getfromint(rt, 900);
    new->value = 0;
    t_obj *ret = ft_makeobj(rt, new, LYCEE);
    return (ret);
}

void	ft_openall(t_rt *rt)
{
	char	*temp;
	char	*ret;
	int		fd;

	ret = ft_strdup("", &rt->garbage);
	if (ret == 0)
		ft_exit(rt, "ERROR");
	if (TEST == 0)
		fd = open("data.json", O_RDONLY);
	if (TEST == 1)
		fd = open("data.json", O_RDONLY);
	if (TEST == 2)
		fd = open("test2.json", O_RDONLY);
	if (TEST == 3)
		fd = open("data.json", O_RDONLY);
	if (fd == -1)
		ft_exit(rt, "Error");
	int i = 0;
	while (1)
	{
		temp = get_next_line(fd, &rt->garbage);
		if (temp == 0)
		{
			close(fd);
			return ;
		}
		ft_parse(rt, temp);
	}
}

int	main()
{
	t_rt	rt;

	ft_initrt(&rt);
	ft_inibtruert(&rt);
	ft_printfirst(&rt);
	mlx_hook(rt.win_ptr, 17, 0, ft_quit, &rt);
	mlx_key_hook(rt.win_ptr, &ft_key_hook, &rt);
	mlx_loop(rt.mlx_ptr);
}
