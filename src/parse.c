#include "../include/rt.h"
#include <stdio.h>

t_coord	atoicoord(t_rt *rt, char *str)
{
	t_coord	coord;
	int		i;

	i = 0;
	coord.x = atoi(&str[i]);
	while (str[i] && str[i] != ',')
		i++;
	if (str[i] == ',')
		i++;
	coord.y = atoi(&str[i]);
	while (str[i] && str[i] != ',')
		i++;
	return (coord);
}

void	calcLycee(t_obj *objet)
{
	t_lycee	*lycee;

	lycee = (t_lycee *)objet->obj;
	objet->xmin = lycee->coord.x - lycee->rayon;
	objet->xmax = lycee->coord.x + lycee->rayon;
	objet->ymin = lycee->coord.y - lycee->rayon;
	objet->ymax = lycee->coord.y + lycee->rayon;
}

void	calcsquare(t_obj *objet)
{
	t_square	*square;

	square = (t_square *)objet->obj;
	objet->xmin = min(square->first.x, square->second.x);
	objet->ymin = min(square->first.y, square->second.y);
	objet->xmax = max(square->first.x, square->second.x);
	objet->ymax = max(square->first.y, square->second.y);
}


void	calccoordobjrt(t_scene *scene, t_obj *obj)
{
	if (obj->xmin < scene->objxmin)
		scene->objxmin = obj->xmin;
	if (obj->ymin < scene->objymin)
		scene->objymin = obj->ymin;
	if (obj->ymax > scene->objymax)
		scene->objymax = obj->ymax;
	if (obj->xmax > scene->objxmax)
		scene->objxmax = obj->xmax;
}

void	calcobj(t_rt *rt, t_obj *objet)
{
	if (objet->type == LYCEE)
		calcLycee(objet);
	else if (objet->type == SQUARE)
		calcsquare(objet);
	calccoordobjrt(&rt->scene, objet);
}

void	*makeobj(t_rt *rt, void *obj, int type)
{
	t_obj	*objet;

	objet = ft_malloc(sizeof(t_obj), &rt->scene.garbage);
	if (!obj)
		ft_exit(rt, "malloc error\n");
	objet->type = type;
	objet->obj = obj;
	calcobj(rt, objet);
	return (objet);
}


char *searchJsonValue(t_rt *rt, char *str, char *toSearch) {
	int	start;
	int end;


	start = ft_strstr(str, toSearch);
	start = start + strlen(toSearch) + 2;
	if (str[start] == '"')
		start++;
	end = ft_strstr(&str[start], "\"");
	if (end == -1) {
		end = strlen(str) - 1;
	}
	end += start;
	return (substr(str, start, end - start, &rt->scene.garbage));
}
void	*makeLycee(t_rt *rt, char *str, t_coord coord)
{
	t_lycee	*new;
	int		i;
	char *end;
	t_coord newCoord;
	double newRadius;

	newCoord.x = strtod(searchJsonValue(rt, str, "Longitude"), &end);
	newCoord.y = strtod(searchJsonValue(rt, str, "Latitude"), &end);
		// printf("newX: %f, newY: %f\n", newCoord.x, newCoord.y);
	if (TEST == 1)
		newRadius = 0.01;

	if (TEST == 1) {
		// printf("newX: %f, newY: %f\n", newCoord.x, newCoord.y);
		if (newCoord.x + newRadius < coord.x) {
			// printf("1");
			return 0;
		}
		if (newCoord.x - newRadius  > coord.x + STEP) {
			// printf("2");
			return 0;
			}
		if (newCoord.y - newRadius < coord.y) {
			// printf("3");
			return 0;
		}
		if (newCoord.y + newRadius > coord.y + STEP) {
			// printf("4");
			return 0;
		}
	}
	else if (TEST == 3) {
		if (newCoord.x < 1.3 || newCoord.x > 3.7 || newCoord.y < 47.9 || newCoord.y > 49.3)
			return 0;
	}
	else if (TEST != 2) {
		if (newCoord.x < -5.15 || newCoord.x > 9.56 || newCoord.y < 41.31 || newCoord.y > 51.1)
			return 0;
	}
	new = ft_malloc(sizeof(t_lycee), &rt->scene.garbage);
	if (!new)
		ft_exit(rt, "malloc error\n");
	new->name = searchJsonValue(rt, str, "Nom_etablissement");
	new->coord = newCoord;
	new->rayon = newRadius;
	if (TEST == 1)
		new->rayon = 0.01;
	if (TEST == 2)
		new->rayon = 20;
	if (TEST == 3)
		new->rayon = 0.01;
	new->color = intToColor(900);
	new->value = 0;
	t_obj *ret = makeobj(rt, new, LYCEE);
	return (ret);
}

void	parse(t_rt *rt, char *in, t_coord coord)
{
	int	i = 0;
	t_obj *new;
	i = ft_strstr(in, "Nom_etablissement");
	if (i != -1) {
		new = makeLycee(rt, in, coord);
		if (new)
		lstnew(new, &rt->scene.obj, &rt->scene.garbage);
	}

}
void	ft_open(t_rt *rt, t_coord coord)
{
	char	*temp;
	char	*ret;
	int		fd;

	ret = ft_strdup("", &rt->scene.garbage);
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
	while (1)
	{
		temp = get_next_line(fd, &rt->scene.garbage);
		if (temp == 0)
		{
			close(fd);
			return ;
		}
		parse(rt, temp, coord);
	}
}
