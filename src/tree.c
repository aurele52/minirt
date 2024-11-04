#include "../include/rt.h"

t_square	*makenewsquare(t_rt *rt, t_coord coord1, t_coord coord2, t_color color)
{
	t_square	*square;

	square = ft_malloc(sizeof(t_square), &rt->scene.garbage);
	if (!square)
		ft_exit(rt, "malloc error\n");
	square->first = coord1;
	square->second = coord2;
	square->color = color;
	return (square);
}

t_square *makefirstsquare(t_rt *rt)
{
	t_coord	*coord1;
	t_coord	*coord2;

	t_square	*square;

	square = ft_malloc(sizeof(t_square), &rt->scene.garbage);
	if (!square)
		ft_exit(rt, "malloc error\n");
	square->first = makecoord(rt, rt->scene.objxmax, rt->scene.objymax);
	square->second = makecoord(rt, rt->scene.objxmin, rt->scene.objymin);
	square->color = intToColor(900);
;
	return (square);
}

t_coord	squaresplit(t_rt *rt, t_square *square)
{
	double	x;
	double	y;

	x = (-square->second.x + square->first.x) / 2 + square->second.x;
	y = (-square->second.y + square->first.y) / 2 + square->second.y;
	return (makecoord(rt, x, y));
}

t_line	*findsplitsquare(t_rt *rt, t_pos *obj, t_square *square, int depth)
{
	t_line	*line;

	line = ft_malloc(sizeof(t_line), &rt->scene.garbage);
	if (!line)
		ft_exit(rt, "malloc error\n");
	if (depth == 0)
	{
		line->coord = squaresplit(rt, square);
		line->ori = makecoord(rt, 0, 1);
		line->color = intToColor(900);
	}
	if (depth == 1)
	{
		line->coord = squaresplit(rt, square);
		line->ori = makecoord(rt, 1, 0);
		line->color = intToColor(900);
	}
	return (line);
}

t_square	*splitsquaregauche(t_rt *rt, t_square *square, t_line *line, int depth)
{
	t_coord	coord1;
	t_coord	coord2;

	if (depth == 0)
	{
		coord1 = makecoord(rt, square->first.x, square->first.y);
		coord2 = makecoord(rt, line->coord.x, square->second.y);
	}
	if (depth == 1)
	{
		coord1 = makecoord(rt, square->first.x, square->first.y);
		coord2 = makecoord(rt, square->second.x, line->coord.y);
	}
	return (makenewsquare(rt, coord1, coord2, intToColor(900)));
}

t_square	*splitsquaredroite(t_rt *rt, t_square *square, t_line *line, int depth)
{
	t_coord	coord1;
	t_coord	coord2;

	if (depth == 0)
	{
		coord1 = makecoord(rt, line->coord.x, square->first.y);
		coord2 = makecoord(rt, square->second.x, square->second.y);
	}
	if (depth == 1)
	{
		coord1 = makecoord(rt, square->first.x, line->coord.y);
		coord2 = makecoord(rt, square->second.x, square->second.y);
	}
	return (makenewsquare(rt, coord1, coord2, intToColor(900)));
}

t_pos	*objRight(t_rt *rt, t_line *line, t_pos *obj, int depth)
{
	t_pos	*new;
	t_list	*mem;
	int		lol;

	lol = 0;
	new = setpos(&rt->scene.garbage);
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
			lstnew(mem->back->content ,new, &rt->scene.garbage);
		}
		else if (((t_obj *)mem->content)->ymin < line->coord.y && depth == 1)
		{
			listToLycee(mem)->color.red += 50;
			mem = mem->next;
			lstnew(mem->back->content ,new, &rt->scene.garbage);
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
	new = setpos(&rt->scene.garbage);
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
			lstnew(mem->back->content ,new, &rt->scene.garbage);
		}
		else if (((t_obj *)mem->content)->ymax > line->coord.y && depth == 1)
		{
			listToLycee(mem)->color.blue += 50;
			mem = mem->next;
			lstnew(mem->back->content ,new, &rt->scene.garbage);
		}
		else
			mem = mem->next;
	}
	return (new);
}

t_bt	*newleaf(t_rt *rt, t_pos *obj)
{
	t_bt *new;

	new = ft_malloc(sizeof(t_bt), &rt->scene.garbage);
	if (!new)
		ft_exit(rt, "malloc error\n");
	new->obj = obj;
	new->right = 0;
	new->racine = 0;
	new->left = 0;
	new->split = 0;
	return (new);
}

t_bt	*newnoeu(t_rt *rt, t_bt *right, t_bt *left, t_line *split)
{
	t_bt	*new;

	new = newleaf(rt, 0);
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
		return (newleaf(rt, obj));
	line = findsplitsquare(rt, obj, square, depth % 2);
	squareRight = splitsquaredroite(rt, square, line, depth % 2);
	squareLeft = splitsquaregauche(rt, square, line, depth % 2);
	history[0] = history[1];
	history[1] = history[2];
	history[2] = obj->size;
	objListLeft = objLeft(rt, line, obj, depth % 2);
	objListRight = objRight(rt, line, obj, depth % 2);
	return (newnoeu(rt, treeConstruct(rt, objListRight, squareRight, depth + 1, history), treeConstruct(rt, objListLeft, squareLeft, depth + 1, history), line));
}

void	makeTree(t_rt *rt)
{
	t_square	*square;
	t_pos	*start;
	t_bt	*tree;
	t_bt	*in;
	int	history[3];

	square = makefirstsquare(rt);
	history[0] = -1;
	history[1] = -1;
	history[2] = -1;
	rt->scene.tree = treeConstruct(rt, &rt->scene.obj, square, 0, history);
}
