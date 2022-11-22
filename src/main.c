/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 21:07:03 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/22 16:34:12 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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

void	ft_printpixelimg(t_rt *rt, t_coord *print, int color)
{
	int		pos;
	char	*pixel;

	if (print->x < 0 || print->y < 0
		|| print->y > rt->ysize || print->x > rt->xsize)
		return ;
	pos = (print->y * rt->image.size_line
			+ print->x * (rt->image.bits_per_pixel / 8));
	pixel = rt->image.imgaddress + pos;
	*(int *)pixel = color;
}

void	ft_printseg(t_rt *rt, t_seg *seg)
{
	ft_printdroite(rt, *seg->first, *seg->second, seg->color);
}

void	ft_printvoxel(t_rt *rt, t_voxel *voxel)
{
	t_coord	third;
	t_coord	fourth;

	third = *ft_makecoord(rt, voxel->first->x, voxel->second->y, 0);
	fourth = *ft_makecoord(rt, voxel->second->x, voxel->first->y, 0);
	ft_printdroite(rt, *voxel->first, third, voxel->color);
	ft_printdroite(rt, third, *voxel->second, voxel->color);
	ft_printdroite(rt, *voxel->second, fourth, voxel->color);
	ft_printdroite(rt, fourth, *voxel->first, voxel->color);
}

void	ft_printpl(t_rt *rt, t_pl *pl)
{
	t_coord	*first;
	t_coord	*second;

	first = ft_makecoord(rt, pl->coord->x + rt->xsize * pl->ori->x, pl->coord->y + rt->ysize * pl->ori->y, 0);
	second = ft_makecoord(rt, pl->coord->x + -(rt->xsize * pl->ori->x), pl->coord->y + -(rt->ysize * pl->ori->y), 0);
	ft_printdroite(rt, *second, *first, pl->color);
	pl->color = pl->color + 10000;
	first = ft_makecoord(rt, pl->coord->x + 10 * pl->ori->y, pl->coord->y + 10 * pl->ori->x, 0);
	ft_printdroite(rt, *pl->coord, *first, pl->color);
}

void	ft_printcam(t_rt *rt, t_cam *cam)
{
	int	x;
	int	y;
	int	x2;
	int	y2;

	x = cam->coord->x + 10;
	y = cam->coord->y;
	x2 = cam->coord->x - 10;
	y2 = cam->coord->y;
	ft_printdroite(rt, *ft_makecoord(rt, x2, y2, 0), *ft_makecoord(rt, x, y, 0), cam->color);
	x = cam->coord->x;
	y = cam->coord->y + 10;
	x2 = cam->coord->x;
	y2 = cam->coord->y - 10;
	ft_printdroite(rt, *ft_makecoord(rt, x2, y2, 0), *ft_makecoord(rt, x, y, 0), cam->color);
}

t_voxel	*ft_makenewvoxel(t_rt *rt, t_coord *coord1, t_coord *coord2, int *color)
{
	t_voxel	*voxel;

	voxel = ft_malloc(sizeof(t_voxel), rt->garbage);
	if (!voxel)
		ft_exit(rt, "malloc error\n");
	voxel->first = coord1;
	voxel->second = coord2;
	voxel->color = *color;
	return (voxel);
}

t_voxel *ft_makefirstvoxel(t_rt *rt)
{
	t_coord	*coord1;
	t_coord	*coord2;

	coord1 = ft_makecoord(rt, rt->objxmax, rt->objymax, rt->objzmax);
	coord2 = ft_makecoord(rt, rt->objxmin, rt->objymin, rt->objzmin);
	return (ft_makenewvoxel(rt, coord1, coord2, rt->color));
}

t_coord	*ft_voxelsplit(t_rt *rt, t_voxel *voxel)
{
	int	x;
	int	y;
	int	z;

	x = (-voxel->second->x + voxel->first->x) / 2 + voxel->second->x;
	y = (-voxel->second->y + voxel->first->y) / 2 + voxel->second->y;
	z = (-voxel->second->z + voxel->first->z) / 2 + voxel->second->z;
	return (ft_makecoord(rt, x, y, z));
}

t_pl	*ft_findsplitvoxel(t_rt *rt, t_pos *obj, t_voxel *voxel, int depth)
{
	t_pl	*pl;

	(void)obj;
	pl = ft_malloc(sizeof(t_pl), rt->garbage);
	if (!pl)
		ft_exit(rt, "malloc error\n");
	if (depth == 0)
	{
		pl->coord = ft_voxelsplit(rt, voxel);
		pl->ori = ft_makecoord(rt, 0, 1, 0);
		pl->color = 77777;
	}
	if (depth == 1)
	{
		pl->coord = ft_voxelsplit(rt, voxel);
		pl->ori = ft_makecoord(rt, 1, 0, 0);
		pl->color = 8888888;
	}
	if (depth == 2)
	{
		pl->coord = ft_voxelsplit(rt, voxel);
		pl->ori = ft_makecoord(rt, 0, 0, 1);
		pl->color = 8888888;
	}
	return (pl);
}

void	ft_printobj(t_rt *rt, t_obj *obj)
{
	if (obj->type == SEG)
		ft_printseg(rt, (t_seg *)obj->obj);
	if (obj->type == VOXEL)
		ft_printvoxel(rt, (t_voxel *)obj->obj);
	if (obj->type == SP)
		ft_printsp(rt, (t_sp *)obj->obj);
	if (obj->type == PL)
		ft_printpl(rt, (t_pl *)obj->obj);
	if (obj->type == C)
		ft_printcam(rt, (t_cam *)obj->obj);
}

void	ft_printobjlist(t_rt *rt, t_pos *print)
{
	t_list	*liste;
	int		mem;

	mem = 0;
	liste = print->start;
	while (liste != print->start || mem++ == 0)
	{
		ft_printobj(rt, (t_obj *)liste->content);
		liste = liste->next;
	}
}

t_voxel	*ft_splitvoxelgauche(t_rt *rt, t_voxel *voxel, t_pl *pl, int depth)
{
	t_coord	*coord1;
	t_coord	*coord2;

	if (depth == 0)
	{
		coord1 = ft_makecoord(rt, voxel->first->x, voxel->first->y, voxel->first->z);
		coord2 = ft_makecoord(rt, pl->coord->x, voxel->second->y, voxel->second->z);
	}
	if (depth == 1)
	{
		coord1 = ft_makecoord(rt, voxel->first->x, voxel->first->y, voxel->first->z);
		coord2 = ft_makecoord(rt, voxel->second->x, pl->coord->y, voxel->second->z);
	}
	if (depth == 2)
	{
		coord1 = ft_makecoord(rt, voxel->first->x, voxel->first->y, voxel->first->z);
		coord2 = ft_makecoord(rt, voxel->second->x, voxel->second->y, pl->coord->z);
	}
	return (ft_makenewvoxel(rt, coord1, coord2, rt->color));
}

t_voxel	*ft_splitvoxeldroite(t_rt *rt, t_voxel *voxel, t_pl *pl, int depth)
{
	t_coord	*coord1;
	t_coord	*coord2;

	if (depth == 0)
	{
		coord1 = ft_makecoord(rt, pl->coord->x, voxel->first->y, voxel->first->z);
		coord2 = ft_makecoord(rt, voxel->second->x, voxel->second->y, voxel->second->z);
	}
	if (depth == 1)
	{
		coord1 = ft_makecoord(rt, voxel->first->x, pl->coord->y, voxel->first->z);
		coord2 = ft_makecoord(rt, voxel->second->x, voxel->second->y, voxel->second->z);
	}
	if (depth == 2)
	{
		coord1 = ft_makecoord(rt, voxel->first->x, voxel->first->y, pl->coord->z);
		coord2 = ft_makecoord(rt, voxel->second->x, voxel->second->y, voxel->second->z);
	}
	return (ft_makenewvoxel(rt, coord1, coord2, rt->color));
}

void	ft_coloradd(t_obj *obj, int color)
{
	t_pl *p;

	p = (t_pl *)obj->obj;
	p->color = p->color + color;
}

t_pos	*ft_objdroite(t_rt *rt, t_pl *pl, t_pos *obj, int depth)
{
	t_pos	*new;
	t_list	*mem;
	int		lol;

	lol = 0;
	new = ft_setpos(rt->garbage);
	if (!new)
		ft_exit(rt, "malloc error\n");
	mem = obj->start;
	if (!mem)
		return (new);
	while (mem != obj->start || !lol++)
	{
		if (((t_obj *)mem->content)->xmin < pl->coord->x && depth == 0)
		{
			ft_coloradd((t_obj *)mem->content, 777777);
			mem = mem->next;
			ft_lstnew(mem->back->content ,new, rt->garbage);
		}
		else if (((t_obj *)mem->content)->ymin < pl->coord->y && depth == 1)
		{
			ft_coloradd((t_obj *)mem->content, 777777);
			mem = mem->next;
			ft_lstnew(mem->back->content ,new, rt->garbage);
		}
		else if (((t_obj *)mem->content)->zmin < pl->coord->z && depth == 2)
		{
			ft_coloradd((t_obj *)mem->content, 777777);
			mem = mem->next;
			ft_lstnew(mem->back->content ,new, rt->garbage);
		}
		else
			mem = mem->next;
	}
	return (new);
}

t_pos	*ft_objgauche(t_rt *rt, t_pl *pl, t_pos *obj, int depth)
{
	t_pos	*new;
	t_list	*mem;
	int		lol;

	lol = 0;
	new = ft_setpos(rt->garbage);
	if (!new)
		ft_exit(rt, "malloc error\n");
	mem = obj->start;
	if (!mem)
		return (new);
	while (mem != obj->start || !lol++)
	{
		if (((t_obj *)mem->content)->xmax > pl->coord->x && depth == 0)
		{
			ft_coloradd((t_obj *)mem->content, 799999);
			mem = mem->next;
			ft_lstnew(mem->back->content ,new, rt->garbage);
		}
		else if (((t_obj *)mem->content)->ymax > pl->coord->y && depth == 1)
		{
			ft_coloradd((t_obj *)mem->content, 799999);
			mem = mem->next;
			ft_lstnew(mem->back->content ,new, rt->garbage);
		}
		else if (((t_obj *)mem->content)->zmax > pl->coord->z && depth == 2)
		{
			ft_coloradd((t_obj *)mem->content, 799999);
			mem = mem->next;
			ft_lstnew(mem->back->content ,new, rt->garbage);
		}
		else
			mem = mem->next;
	}
	return (new);
}

void	ft_clearobjlist(t_pl *pl, t_pos *obj, int depth)
{
	t_list	*mem;
	int		lol;

	lol = 0;
	mem = obj->start;
	if (!mem)
		return ;
	while (*mem->pos->size != 0 && (mem != obj->start || !lol++))
	{
		if ((((t_obj *)mem->content)->xmax != pl->coord->x || ((t_obj *)mem->content)->xmin != pl->coord->x) && depth == 0)
		{
			lol--;
			mem = mem->next;
			ft_lstdelone(mem->back ,0);
		}
		else if ((((t_obj *)mem->content)->ymax != pl->coord->y || ((t_obj *)mem->content)->ymin != pl->coord->y) && depth == 1)
		{
			lol--;
			mem = mem->next;
			ft_lstdelone(mem->back ,0);
		}
		else if ((((t_obj *)mem->content)->zmax != pl->coord->z || ((t_obj *)mem->content)->zmin != pl->coord->z) && depth == 2)
		{
			lol--;
			mem = mem->next;
			ft_lstdelone(mem->back ,0);
		}
		else
			mem = mem->next;
	}
}

t_pos	*ft_lstdup(t_pos *pos, t_pos *garbage)
{
	t_pos	*new;
	t_list	*liste;
	int	i;

	i = 0;
	liste = pos->start;
	new = ft_setpos(garbage);
	while (i < *pos->size)
	{
		ft_lstnew(liste->content, new, garbage);
		liste = liste->next;
		i++;
	}
	return (new);
}

int	ft_calcfin(t_pos *obj, t_voxel *voxel, int depth)
{
	if (*obj->size <= 1)
		return (1);
	return (0);
	(void)voxel;
	(void)obj;
	(void)depth;
}

t_bt	*ft_newleaf(t_rt *rt, t_pos *obj)
{
	t_bt *new;

	new = ft_malloc(sizeof(t_bt), rt->garbage);
	if (!new)
		ft_exit(rt, "malloc error\n");
	new->obj = obj;
	new->right = 0;
	new->racine = 0;
	new->left = 0;
	return (new);
}

t_bt	*ft_newnoeu(t_rt *rt, t_pos *obj, t_bt *right, t_bt *left)
{
	t_bt	*new;

	new = ft_newleaf(rt, obj);
	right->racine = new;
	left->racine = new;
	new->left = left;
	new->right = right;
	new->racine = 0;
	return (new);
}

void	ft_printpl2(t_rt *rt, t_pl *pl, t_voxel *voxel)
{
	t_coord	*first;
	t_coord	*second;

	first = ft_makecoord(rt, pl->coord->x + rt->xsize * pl->ori->x, pl->coord->y + rt->ysize * pl->ori->y, 0);
	if (first->x > voxel->first->x)
		first->x = voxel->first->x;
	if (first->y > voxel->first->y)
		first->y = voxel->first->y;
	second = ft_makecoord(rt, pl->coord->x + -(rt->xsize * pl->ori->x), pl->coord->y + -(rt->ysize * pl->ori->y), 0);
	if (second->x < voxel->second->x)
		second->x = voxel->second->x;
	if (second->y < voxel->second->y)
		second->y = voxel->second->y;
	ft_printdroite(rt, *second, *first, pl->color);
	pl->color = pl->color + 10000;
	first = ft_makecoord(rt, pl->coord->x + 10 * pl->ori->y, pl->coord->y + 10 * pl->ori->x, 0);
	ft_printdroite(rt, *pl->coord, *first, pl->color);
}

t_bt	*ft_voxeluconstruct(t_rt *rt, t_pos *obj, t_voxel *voxel, int depth)
{
	t_pl	*plan;
	t_voxel	*voxeldroite;
	t_voxel	*voxelgauche;
	t_pos	*listevoxeldroite;
	t_pos	*listevoxelgauche;

	if (ft_calcfin(obj, voxel, depth))
		return (ft_newleaf(rt, obj));
	plan = ft_findsplitvoxel(rt, obj, voxel, depth % 3);
	if (depth % 3 != 2)
	ft_printpl2(rt, plan, voxel);
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->image.origin, 0, 0);
	voxeldroite = ft_splitvoxeldroite(rt, voxel, plan, depth % 3);
	voxelgauche = ft_splitvoxelgauche(rt, voxel, plan, depth % 3);
	listevoxeldroite = ft_objdroite(rt, plan, obj, depth % 3);
	listevoxelgauche = ft_objgauche(rt, plan, obj, depth % 3);
	ft_clearobjlist(plan, obj, depth % 3);
	ft_printobjlist(rt, rt->obj);
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->image.origin, 0, 0);
	return (ft_newnoeu(rt, obj, ft_voxeluconstruct(rt, listevoxeldroite, voxeldroite, depth + 1), ft_voxeluconstruct(rt, listevoxelgauche, voxelgauche, depth + 1)));
}
/*
t_noeu	*ft_constructtree(t_rt *rt)
*/
void	ft_constructtree(t_rt *rt)
{
	t_voxel	*voxel;
	t_pos	*start;

	start = ft_lstdup(rt->obj, rt->garbage);
	voxel = ft_makefirstvoxel(rt);
	ft_printvoxel(rt, voxel);
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->image.origin, 0, 0);
	ft_voxeluconstruct(rt, start, voxel, 0);
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

void	ft_inittruert(t_rt *rt)
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

t_coord	*ft_atoicoord(t_rt *rt, char *str)
{
	t_coord	*coord;
	int		i;

	i = 0;
	coord = ft_malloc(sizeof(t_coord), rt->garbage);
	if (!coord)
		ft_exit(rt, "malloc error\n");
	coord->x = ft_atoi(&str[i]);
	while (str[i] && str[i] != ',')
		i++;
	if (str[i] == ',')
		i++;
	coord->y = ft_atoi(&str[i]);
	while (str[i] && str[i] != ',')
		i++;
	if (str[i] == ',')
		i++;
	coord->z = ft_atoi(&str[i]);
	return (coord);
}

t_coord	*ft_atoiori(t_rt *rt, char *str)
{
	t_coord	*ori;
	int		i;

	i = 0;
	ori = ft_malloc(sizeof(t_coord), rt->garbage);
	if (!ori)
		ft_exit(rt, "malloc error\n");
	ori->x = ft_atoi(&str[i]);
	while (str[i] && str[i] != ',')
		i++;
	if (str[i] == ',')
		i++;
	ori->y = ft_atoi(&str[i]);
	while (str[i] && str[i] != ',')
		i++;
	if (str[i] == ',')
		i++;
	ori->z = ft_atoi(&str[i]);
	return (ori);
}

void	ft_calcsp(t_obj *objet)
{
	t_sp	*sp;

	sp = (t_sp *)objet->obj;
	objet->xmin = sp->coord->x - sp->rayon;
	objet->xmax = sp->coord->x + sp->rayon;
	objet->ymin = sp->coord->y - sp->rayon;
	objet->ymax = sp->coord->y + sp->rayon;
	objet->zmin = sp->coord->z - sp->rayon;
	objet->zmax = sp->coord->z + sp->rayon;
}

void	ft_calcpl(t_obj *objet)
{
	t_pl	*pl;

	pl = (t_pl *)objet->obj;
	if (pl->ori->x == 0)
	{
		objet->xmin = pl->coord->x;
		objet->xmax = pl->coord->x;
	}
	else
	{
		objet->xmin = -2000000000;
		objet->xmax = 2000000000;
	}
	if (pl->ori->y == 0)
	{
		objet->ymin = pl->coord->y;
		objet->ymax = pl->coord->y;
	}
	else
	{
		objet->ymin = -2000000000;
		objet->ymax = 2000000000;
	}
	if (pl->ori->z == 0)
	{
		objet->zmin = pl->coord->z;
		objet->zmax = pl->coord->z;
	}
	else
	{
		objet->ymin = -2000000000;
		objet->ymax = 2000000000;
	}
}

void	ft_calcvoxel(t_obj *objet)
{
	t_voxel	*voxel;

	voxel = (t_voxel *)objet->obj;
	objet->xmin = ft_min(voxel->first->x, voxel->second->x);
	objet->ymin = ft_min(voxel->first->y, voxel->second->y);
	objet->xmax = ft_max(voxel->first->x, voxel->second->x);
	objet->ymax = ft_max(voxel->first->y, voxel->second->y);
	objet->zmin = ft_min(voxel->first->z, voxel->second->z);
	objet->zmax = ft_max(voxel->first->z, voxel->second->z);
}

void	ft_calcC(t_obj *objet)
{
	t_cam	*cam;

	cam = (t_cam *)objet->obj;
	objet->xmin = cam->coord->x;
	objet->ymin = cam->coord->y;
	objet->xmax = cam->coord->x;
	objet->ymax = cam->coord->y;
	objet->zmin = cam->coord->z;
	objet->zmax = cam->coord->z;
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
	if (obj->zmin < rt->objzmin)
		rt->objzmin = obj->zmin;
	if (obj->zmax > rt->objzmax)
		rt->objzmax = obj->zmax;
}

void	ft_recalc(t_rt *rt)
{
	t_list	*liste;
	int		mem;

	rt->objxmin = 200000000;
	rt->objxmax = -200000000;
	rt->objymin = 200000000;
	rt->objymax = -200000000;
	rt->objzmin = 200000000;
	rt->objzmax = -200000000;
	mem = 0;
	liste = rt->obj->start;
	while (liste != rt->obj->start || mem++ == 0)
	{
		ft_calccoordobjrt(rt, (t_obj *)liste->content);
		liste = liste->next;
	}
}

void	ft_calcobj(t_rt *rt, t_obj *objet)
{
	if (objet->type == SP)
		ft_calcsp(objet);
	else if (objet->type == VOXEL)
		ft_calcvoxel(objet);
	else if (objet->type == PL)
		ft_calcpl(objet);
	else if (objet->type == C)
		ft_calcC(objet);
	else if (objet->type == L)
		ft_calcC(objet);
	ft_calccoordobjrt(rt, objet);
}

void	ft_moveonecoord(void *obj, t_coord *coord)
{
	t_sp	*sp;

	sp = (t_sp *)obj;
	if (coord->x != 0)
		sp->coord->x = sp->coord->x + coord->x;
	if (coord->y != 0)
		sp->coord->y = sp->coord->y + coord->y;
	if (coord->z != 0)
		sp->coord->z = sp->coord->z + coord->z;
}

int		ft_isonecoordex(t_rt *rt, void *obj)
{
	t_coord	*coord;

	coord = ((t_sp *)obj)->coord;
	if (coord->x == rt->objxmin || coord->x == rt->objxmax)
		return (1);
	if (coord->y == rt->objymin || coord->y == rt->objymax)
		return (1);
	if (coord->z == rt->objzmin || coord->z == rt->objzmax)
		return (1);
	return (0);
}

void	ft_moveobj(t_rt *rt, t_obj *obj, t_coord *dep)
{
	int	mem;

	if (obj->type == C || obj->type == SP)
	{
		mem = ft_isonecoordex(rt, obj->obj);
		ft_moveonecoord((t_sp *)obj->obj, dep);
		ft_calcobj(rt, obj);
		if (mem)
			ft_recalc(rt);
	}
}

float	ft_normcarre(t_coord *one)
{
	return (one->x * one->x + one->y * one->y + one->z * one->z);
}

float	ft_scalaire(t_coord *one, t_coord two)
{
	return (one->x * two.x + one->y * two.y + one->z * two.z);
}

void	ft_norm(t_coord *one)
{
	float	norm;

	norm = sqrt(ft_normcarre(one));
	one->x = one->x / norm;
	one->y = one->y / norm;
	one->z = one->z / norm;
}

int	ft_intersection(t_rt *rt ,t_ray *rayon, t_obj *obj)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float	sol1;
	float	sol2;


	a = 1;
	b = 2 * ft_scalaire(rayon->ori, *rt->origin - *((t_sp *)obj->obj)->coord);
	c = ft_normcarre(((t_sp *)obj->obj)->coord) - ((t_sp *)obj->obj)->rayon * ((t_sp *)obj->obj)->rayon;
	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (0);
	sol1 = (-b -(sqrt(delta))) / (2 * a);
	sol2 = (-b +(sqrt(delta))) / (2 * a);
	if (sol2 > 0)
		return (1);
	return (0);
}

void	ft_firsttracing(t_rt *rt)
{
	int		i;
	int		j;
	t_ray 	rayon;
	int		inter;

	i = 0;
	j = 0;
	while (j < rt->ysize - 1)
	{
		while (i < rt->xsize - 1)
		{
			rayon.coord = ((t_cam *)rt->cam->obj)->coord;
			rayon.ori = ft_makecoord(rt, i - rt->xsize / 2, j - rt->ysize / 2, -rt->xsize / (2 * tan(rt->fov / 2)));
			ft_norm(rayon.ori);
			inter = ft_intersection(rt, &rayon, rt->obj->start->next->content);
			if (inter == 0)
				ft_printpixelimg(rt, ft_makecoord(rt, i, j, 0), 55555);
			else
				ft_printpixelimg(rt, ft_makecoord(rt, i, j, 0), 333);
			i++;
		}
		i = 0;
		j++;
	}
}

void	ft_printfirst(t_rt *rt)
{
	ft_constructtree(rt);
//	ft_printobjlist(rt, rt->obj);
//	ft_firsttracing(rt);
}

int	ft_key_hook(int keycode, t_rt *rt)
{
	if (keycode == 65361)
		ft_moveobj(rt, rt->cam, ft_makecoord(rt, -10, 0, 0));
	if (keycode == 65362)
		ft_moveobj(rt, rt->cam, ft_makecoord(rt, 0, -10, 0));
	if (keycode == 65363)
		ft_moveobj(rt, rt->cam, ft_makecoord(rt, 10, 0, 0));
	if (keycode == 65364)
		ft_moveobj(rt, rt->cam, ft_makecoord(rt, 0, 10, 0));
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

	objet = ft_malloc(sizeof(t_obj), rt->garbage);
	if (!obj)
		ft_exit(rt, "malloc error\n");
	objet->type = type;
	objet->obj = obj;
	if (type == L)
		rt->light = objet;
	if (type == C)
		rt->cam = objet;
	ft_calcobj(rt, objet);
	return (objet);
}

void	*ft_makeseg(t_rt *rt, char *str)
{
	t_seg	*seg;
	int		i;

	i = 0;
	seg = ft_malloc(sizeof(t_seg), rt->garbage);
	if (!seg)
		ft_exit(rt, "malloc error\n");
	while (str[i] == ' ')
		i++;
	seg->first = ft_atoicoord(rt, &str[i]);
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i] == ' ')
		i++;
	seg->second = ft_atoicoord(rt, &str[i]);
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i] == ' ')
		i++;
	seg->color = ft_atoi(&str[i]);
	return (ft_makeobj(rt, seg, SEG));
}

void	*ft_makevoxel(t_rt *rt, char *str)
{
	t_voxel	*voxel;
	int		i;

	i = 0;
	voxel = ft_malloc(sizeof(t_voxel), rt->garbage);
	if (!voxel)
		ft_exit(rt, "malloc error\n");
	while (str[i] == ' ')
		i++;
	voxel->first = ft_atoicoord(rt, &str[i]);
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i] == ' ')
		i++;
	voxel->second = ft_atoicoord(rt, &str[i]);
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i] == ' ')
		i++;
	voxel->color = ft_atoi(&str[i]);
	return (ft_makeobj(rt, voxel, VOXEL));
}

void	*ft_makesp(t_rt *rt, char *str)
{
	t_sp	*sp;
	int		i;

	i = 0;
	sp = ft_malloc(sizeof(t_sp), rt->garbage);
	if (!sp)
		ft_exit(rt, "malloc error\n");
	while (str[i] == ' ')
		i++;
	sp->coord = ft_atoicoord(rt, &str[i]);
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i] == ' ')
		i++;
	sp->rayon = ft_atoi(&str[i]);
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i] == ' ')
		i++;
	sp->color = ft_atoi(&str[i]);
	return (ft_makeobj(rt, sp, SP));
}

void	*ft_makepl(t_rt *rt, char *str)
{
	t_pl	*pl;
	int		i;

	i = 0;
	pl = ft_malloc(sizeof(t_pl), rt->garbage);
	if (!pl)
		ft_exit(rt, "malloc error\n");
	while (str[i] == ' ')
		i++;
	pl->coord = ft_atoicoord(rt, &str[i]);
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i] == ' ')
		i++;
	pl->ori = ft_atoiori(rt, &str[i]);
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i] == ' ')
		i++;
	pl->color = ft_atoi(&str[i]);
	return (ft_makeobj(rt, pl, PL));
}

void	*ft_makecam(t_rt *rt, char *str)
{
	t_cam	*cam;
	int		i;

	i = 0;
	cam = ft_malloc(sizeof(t_cam), rt->garbage);
	if (!cam)
		ft_exit(rt, "malloc error\n");
	while (str[i] == ' ')
		i++;
	cam->coord = ft_atoicoord(rt, &str[i]);
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i] == ' ')
		i++;
	cam->color = ft_atoi(&str[i]);
	return (ft_makeobj(rt, cam, C));
}

void	*ft_makelight(t_rt *rt, char *str)
{
	t_light	*light;
	int		i;

	i = 0;
	light = ft_malloc(sizeof(t_light), rt->garbage);
	if (!light)
		ft_exit(rt, "malloc error\n");
	while (str[i] == ' ')
		i++;
	light->coord = ft_atoicoord(rt, &str[i]);
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i] == ' ')
		i++;
	light->intensiter = ft_atoi(&str[i]);
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i] == ' ')
		i++;
	light->color = ft_atoi(&str[i]);
	return (ft_makeobj(rt, light, L));
}

void	ft_parse(t_rt *rt, char	**in)
{
	int	i;

	i = 0;
	while (in[i])
	{
		if (in[i][0] == 's' && in[i][1] == 'e' && in[i][2] == 'g')
			ft_lstnew(ft_makeseg(rt, &in[i][3]), rt->obj, rt->garbage);
		if (in[i][0] == 'r' && in[i][1] == 'e' && in[i][2] == 'c')
			ft_lstnew(ft_makevoxel(rt, &in[i][3]), rt->obj, rt->garbage);
		if (in[i][0] == 's' && in[i][1] == 'p')
			ft_lstnew(ft_makesp(rt, &in[i][2]), rt->obj, rt->garbage);
		if (in[i][0] == 'p' && in[i][1] == 'l')
			ft_lstnew(ft_makepl(rt, &in[i][2]), rt->obj, rt->garbage);
		if (in[i][0] == 'C')
			ft_lstnew(ft_makecam(rt, &in[i][1]), rt->obj, rt->garbage);
		if (in[i][0] == 'L')
			ft_lstnew(ft_makelight(rt, &in[i][1]), rt->obj, rt->garbage);
		i++;
	}
}

void	ft_open(t_rt *rt, char *str)
{
	char	*temp;
	char	*ret;
	int		fd;

	ret = ft_strdup("", rt->garbage);
	if (ret == 0)
		ft_exit(rt, "ERROR");
	fd = open(str, O_RDONLY);
	if (fd == -1)
		ft_exit(rt, "Error");
	while (1)
	{
		temp = get_next_line(fd, rt->garbage);
		if (temp == 0)
		{
			ft_parse(rt, ft_split(ret, '\n', rt->garbage));
			close(fd);
			return ;
		}
		ret = ft_strjoin(ret, temp, rt->garbage);
		if (ret == 0)
			ft_exit(rt, "ERROR");
	}
}

void	ft_rtcolor(t_rt *rt)
{
	rt->color = ft_malloc(sizeof(int), rt->garbage);
	if (!rt->color)
		ft_exit(rt, "malloc error\n");
	*rt->color = 777777;
}

t_rt	*ft_initrt(char **argv)
{
	t_rt	*rt;
	t_pos	*garbage;

	(void)argv;
	garbage = ft_setpos(0);
	if (!garbage)
		ft_exit(0, "error malloc");
	rt = ft_malloc(sizeof(t_rt), garbage);
	if (!rt)
	{
		ft_posclear(garbage, 2);
		ft_exit(0, "error malloc");
	}
	rt->garbage = garbage;
	rt->obj = ft_setpos(garbage);
	if (!rt->obj)
		ft_exit(rt, "error malloc");
	ft_rtcolor(rt);
	rt->win_ptr = 0;
	rt->mlx_ptr = 0;
	rt->objxmin = 200000000;
	rt->objxmax = -200000000;
	rt->objymin = 200000000;
	rt->objymax = -200000000;
	rt->objzmin = 200000000;
	rt->objzmax = -200000000;
	rt->fov = 60 * M_PI / 180;
	rt->xsize = 1400;
	rt->ysize = 1400;
	rt->origin = ft_makecoord(rt, 0, 0, 0);
	rt->image.origin = 0;
	ft_open(rt, argv[1]);
	return (rt);
}

int	main(int argc, char **argv)
{
	t_rt	*rt;

	if (argc == 1)
		return (0);
	rt = ft_initrt(argv);
	ft_inittruert(rt);
	ft_printfirst(rt);
	mlx_hook(rt->win_ptr, 17, 0, ft_quit, rt);
	mlx_key_hook(rt->win_ptr, &ft_key_hook, rt);
	mlx_loop(rt->mlx_ptr);
}
