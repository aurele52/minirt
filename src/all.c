#include "../include/rt.h"

int	quit(t_rt *rt)
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

void	printobjlist(t_rt *rt, t_pos *print)
{
	t_list	*liste;
	int		mem;

	if (!print || print->size == 0)
		return;
	mem = 0;
	liste = print->start;
	while (liste != print->start || mem++ == 0)
	{
		printobj(rt, (t_obj *)liste->content);
		liste = liste->next;
	}
}


void	printLineInSquare(t_rt *rt, t_line *line, t_square *square)
{
	t_coord	first;
	t_coord	second;

	first = makecoord(rt, line->coord.x + rt->xsize * line->ori.x, line->coord.y + rt->ysize * line->ori.y);
	if (first.x > square->first.x)
		first.x = square->first.x;
	if (first.y > square->first.y)
		first.y = square->first.y;
	second = makecoord(rt, line->coord.x + -(rt->xsize * line->ori.x), line->coord.y + -(rt->ysize * line->ori.y));
	if (second.x < square->second.x)
		second.x = square->second.x;
	if (second.y < square->second.y)
		second.y = square->second.y;
	printdroite(rt, second, first, line->color);
	line->color.red = line->color.red + 30;
	line->color.green = line->color.green + 30;
	first = makecoord(rt, line->coord.x + 10 * line->ori.y, line->coord.y + 10 * line->ori.x);
	printdroite(rt, line->coord, first, line->color);
}


// void	printList(t_rt *rt, t_pos *pos) {
// 	t_list	*liste;
// 	int		mem;
// 	static int		lol = 0;
//
// 	if (!pos || pos->size == 0) {
// 		return;
// 	}
// 	mem = 0;
// 	liste = pos->start;
// 	while (liste != pos->start || mem++ == 0)
// 	{
// 			// printf("%s\n", listToLycee(liste)->name);
// 		if (listToLycee(liste)->value >= lol) {
// 			lol = listToLycee(liste)->value;
// 			printf("act: %s\n", listToLycee(liste)->name);
// 			printf("value: %f\n", listToLycee(liste)->value);
// 		}
//
// 		liste = liste->next;
// 	}
// }
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
		// printLycee(rt, add);
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
	printObjListName(rt, tree->obj);
	// printobjlist(rt, tree->obj);
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

void	clearImg(t_rt *rt)
{


	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < rt->ysize)
	{
		while (x < rt->xsize)
		{
				int pos = ((int)y * rt->image.size_line
					+ (int)x * (rt->image.bits_per_pixel / 8));
				char *pixel = rt->image.imgaddress + pos;
				*(int *)pixel = 0;
			x++;
		}
		y++;
		x = 0;
	}
}

void	initMinilibx(t_rt *rt)
{
	rt->mlx_ptr = mlx_init();
	if (rt->mlx_ptr == 0)
		ft_exit(rt, "Error");
	rt->win_ptr = mlx_new_window(rt->mlx_ptr, rt->xsize, rt->ysize, "rt");
	if (rt->win_ptr == 0)
		quit(rt);
	rt->image.origin = mlx_new_image(rt->mlx_ptr, rt->xsize, rt->ysize);
	if (rt->image.origin == 0)
		quit(rt);
	rt->image.imgaddress = mlx_get_data_addr(rt->image.origin,
			&rt->image.bits_per_pixel,
			&rt->image.size_line, &rt->image.endian);
}


int	coordInCircle(t_coord coord, t_lycee *lycee) {
	double distance = sqrt(pow(coord.x - lycee->coord.x, 2) + pow(coord.y - lycee->coord.y, 2));
	if (distance <= lycee->rayon) {
		return 1;
	}
	return 0;
}
char *tempname = 0;
double tempvalue = 0;
double templatitude = 0;
double templongitude = 0;

void	calcInside(t_rt *rt, t_lycee *lyc, t_pos *obj) {
	t_list	*liste;
	t_bt	*find;
	int		mem;
	int add =0;

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
	if (add >= tempvalue) {
		tempvalue = add;
		tempname = lyc->name;
		templatitude = lyc->coord.y;
		templongitude = lyc->coord.x;
		// printf("name: %s\n", lyc->name);
		// printf("value: %d\n", lol);

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
	while (liste != pos->start || mem++ == 0)
	{
			// printf("%s\n", listToLycee(liste)->name);
		if (listToLycee(liste)->value >= maxToParse) {
			find = searchCoordInTree(rt, rt->scene.tree, listToLycee(liste)->coord);
			if (find) {
				calcInside(rt, listToLycee(liste), find->obj);
			}
		}
		liste = liste->next;
	}
}

void	findCoordMax(t_rt *rt) {
	printListMax(rt, &rt->scene.obj);
}

void	printScene(t_rt *rt)
{
	clearImg(rt);
	makeTree(rt);
	findCoordMax(rt);
	if (tempname)
		printf("name: %s\nvalue: %f\n\n", tempname, tempvalue);
	tempname = 0;
	tempvalue = 0;
	printobjlist(rt, &rt->scene.obj);
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->image.origin, 0, 0);
}

void	resetScene(t_rt *rt);
void	printScene2(t_rt *rt)
{
	static t_coord one = {-5.15, 41.31};
	one.x += STEP;
	if (one.x > 9.56 + STEP) {
		one.x = -5.15;
		one.y += STEP;
	}
	// static int obj = 0;
	// obj += rt->scene.obj.size;
	if (one.y > 51.3 + STEP)
		ft_exit(rt, "");
	resetScene(rt);
	clearImg(rt);
	ft_open(rt, one);
	makeTree(rt);
	findCoordMax(rt);
	if (tempname)
		printf("{\"name\":\"%s\",\"value\":\"%f\",\"latitude\":\"%f\",\"longitude\":\"%f\"},", tempname, tempvalue, templatitude, templongitude);
	tempname = 0;
	tempvalue = 0;
	// printobjlist(rt, &rt->scene.obj);
	// printf("%d\n", obj);
	// mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->image.origin, 0, 0);
}

int	keyHook(int keycode, t_rt *rt)
{
	if (keycode == 65307)
		quit(rt);
	clearImg(rt);
	printScene2(rt);
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->image.origin, 0, 0);
	return (keycode);
}


int	ft_strstr(const char *big, const char *libtle) {
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;

	int bigLen = strlen(big);
	int libtleLen = strlen(libtle);
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





void	resetScene(t_rt *rt) {
	if (rt->scene.garbage.size != 0)
		posclear(&rt->scene.garbage, 1);
	rt->scene.obj.start = 0;
	rt->scene.obj.end = 0;
	rt->scene.obj.size = 0;
	rt->scene.tree = 0;
	rt->scene.objxmin = -2000;
	rt->scene.objymin = -2000;
	rt->scene.objxmax = 2000;
	rt->scene.objymax = 2000;
}

void	initrt(t_rt *rt)
{
	t_pos	*garbage;

	rt->garbage.start = 0;
	rt->garbage.end = 0;
	rt->garbage.size = 0;
	rt->scene.garbage.size = 0;
	rt->scene.garbage.end = 0;
	rt->scene.garbage.start = 0;
	rt->scene.obj.start = 0;
	rt->scene.obj.end = 0;
	rt->scene.obj.size = 0;
	rt->scene.tree = 0;
	rt->scene.objxmin = 2000;
	rt->scene.objymin = 2000;
	rt->scene.objxmax = -2000;
	rt->scene.objymax = -2000;
	rt->win_ptr = 0;
	rt->mlx_ptr = 0;
	rt->xsize = 1000;
	rt->ysize = 1000;
	rt->origin = makecoord(rt, 0, 0);
	rt->image.origin = 0;
}

void	real(t_rt *rt) {
	t_coord one;
	one.x = -5.15;
	one.y = 41.31;
	ft_open(rt, one);
	printScene(rt);

}



int	main() {
	t_rt	rt;

	initrt(&rt);
	initMinilibx(&rt);
	real(&rt);
	mlx_hook(rt.win_ptr, 17, 0, quit, &rt);
	mlx_key_hook(rt.win_ptr, &keyHook, &rt);
	mlx_loop(rt.mlx_ptr);
}
