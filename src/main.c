/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 21:07:03 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/10 16:16:53 by audreyer         ###   ########.fr       */
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

void	ft_printpixelimg(t_rt *rt, t_coord *print)
{
	int		pos;
	char	*pixel;

	if (print->x < 0 || print->y < 0
		|| print->y > rt->ysize || print->x > rt->xsize)
		return ;
	pos = (print->y * rt->image.size_line
			+ print->x * (rt->image.bits_per_pixel / 8));
	pixel = rt->image.imgaddress + pos;
	*(int *)pixel = print->color;
}

void	ft_printseg(t_rt *rt, t_seg *seg)
{
	ft_printdroite(rt, *seg->first, *seg->second);
}

void	ft_printvoxel(t_rt *rt, t_voxel *voxel)
{
	t_coord	third;
	t_coord	fourth;

	third = *ft_makecoord(rt, voxel->first->x, voxel->second->y, voxel->color);
	fourth = *ft_makecoord(rt, voxel->second->x, voxel->first->y, voxel->color);
	ft_printdroite(rt, *voxel->first, third);
	ft_printdroite(rt, third, *voxel->second);
	ft_printdroite(rt, *voxel->second, fourth);
	ft_printdroite(rt, fourth, *voxel->first);
}

void	ft_printpl(t_rt *rt, t_pl *pl)
{
	t_coord	*first;
	t_coord	*second;

	first = ft_makecoord(rt, pl->coord->x + rt->xsize * pl->ori->x, pl->coord->y + rt->ysize * pl->ori->y, pl->color);
	second = ft_makecoord(rt, pl->coord->x + -(rt->xsize * pl->ori->x), pl->coord->y + -(rt->ysize * pl->ori->y), pl->color);
	ft_printdroite(rt, *second, *first);
}

void	ft_printcam(t_rt *rt, t_cam *cam)
{
	int	x;
	int	y;
	int	x2;
	int	y2;

	(void)cam;
	x = rt->cam->coord->x + 10;
	y = rt->cam->coord->y;
	x2 = rt->cam->coord->x - 10;
	y2 = rt->cam->coord->y;
	ft_printdroite(rt, *ft_makecoord(rt, x2, y2, 123233), *ft_makecoord(rt, x, y, 123233));
	x = rt->cam->coord->x;
	y = rt->cam->coord->y + 10;
	x2 = rt->cam->coord->x;
	y2 = rt->cam->coord->y - 10;
	ft_printdroite(rt, *ft_makecoord(rt, x2, y2, 123233), *ft_makecoord(rt, x, y, 123233));
}

void	ft_printobj(t_rt *rt)
{
	t_list	*liste;
	int		mem;

	mem = 0;
	liste = rt->obj->start;
	while (liste != rt->obj->start || mem++ == 0)
	{
		if (ft_type(liste) == SEG)
			ft_printseg(rt, ft_seg(liste));
		if (ft_type(liste) == VOXEL)
			ft_printvoxel(rt, ft_voxel(liste));
		if (ft_type(liste) == SP)
			ft_printsp(rt, ft_sp(liste));
		if (ft_type(liste) == PL)
			ft_printpl(rt, ft_pl(liste));
		if (ft_type(liste) == C)
			ft_printcam(rt, ft_C(liste));
		liste = liste->next;
	}
}

t_voxel	*ft_makenewvoxel(t_rt *rt, t_coord *coord1, t_coord *coord2, int color)
{
	t_voxel	*voxel;

	voxel = ft_malloc(sizeof(t_voxel), rt->garbage);
	if (!voxel)
		ft_exit(rt, "malloc error\n");
	voxel->first = coord1;
	voxel->second = coord2;
	voxel->first->color = color;
	voxel->second->color = color;
	voxel->color = color;
	return (voxel);
}

t_voxel *ft_makefirstvoxel(t_rt *rt)
{
	t_coord	*coord1;
	t_coord	*coord2;

	coord1 = ft_makecoord(rt, rt->objxmax, rt->objymax, 5555);
	coord2 = ft_makecoord(rt, rt->objxmin, rt->objymin, 5555);
	return (ft_makenewvoxel(rt, coord1, coord2, 5555));
}
/*
t_noeu	*ft_voxeluconstruct(t_pos *obj, t_voxel *voxel)
{
	if (ft_calcfin(obj, voxel))
		return (ft_newfeuille);
	plan = ft_findsplitvoxel(obj, voxel);
	voxelgauche = ft_splitvoxelgauche(voxel, plan);
	voxeldoite = ft_splitvoxelgauche(voxel, plan);
	listevoxeldroite = ft_objdroite(plan, obj);
	listevoxelgauche = ft_objgauche(plan, obj);
	return (ft_newnoeu(plan, ft_voxeluconstruct(listevoxeldroite, voxeldroit), ft_voxeluconstruct(listevoxelgauche, voxelgauche)));
}
*/
//t_racine	*ft_constructtree(t_rt *rt)
void	ft_constructtree(t_rt *rt)
{
	t_voxel	*voxel;

	voxel = ft_makefirstvoxel(rt);
	ft_printvoxel(rt, voxel);
//	return (ft_voxeluconstruct(obj, voxel));
}

void	ft_printfirst(t_rt *rt)
{
	ft_printobj(rt);
	ft_constructtree(rt);
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

int	ft_key_hook(int keycode, t_rt *rt)
{
	if (keycode == 65361)
		rt->cam->coord->x = rt->cam->coord->x - 10;
	if (keycode == 65362)
		rt->cam->coord->y = rt->cam->coord->y - 10;
	if (keycode == 65363)
		rt->cam->coord->x = rt->cam->coord->x + 10;
	if (keycode == 65364)
		rt->cam->coord->y = rt->cam->coord->y + 10;
	if (keycode == 65307)
		ft_quit(rt);
	ft_clearimg(rt);
	ft_printfirst(rt);
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->image.origin, 0, 0);
	return (keycode);
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
	coord->color = 0;
	return (coord);
}

t_ori	*ft_atoiori(t_rt *rt, char *str)
{
	t_ori	*ori;
	int		i;

	i = 0;
	ori = ft_malloc(sizeof(t_ori), rt->garbage);
	if (!ori)
		ft_exit(rt, "malloc error\n");
	ori->x = ft_atoi(&str[i]);
	while (str[i] && str[i] != ',')
		i++;
	if (str[i] == ',')
		i++;
	ori->y = ft_atoi(&str[i]);
	return (ori);
}

void	ft_calcsp(t_obj *objet, t_sp *sp)
{
	objet->xmin = sp->coord->x - sp->rayon;
	objet->xmax = sp->coord->x + sp->rayon;
	objet->ymin = sp->coord->y - sp->rayon;
	objet->ymax = sp->coord->y + sp->rayon;
}

void	ft_calcpl(t_obj *objet, t_pl *pl)
{
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
}

void	ft_calcvoxel(t_obj *objet, t_voxel *voxel)
{
	objet->xmin = ft_min(voxel->first->x, voxel->second->x);
	objet->ymin = ft_min(voxel->first->y, voxel->second->y);
	objet->xmax = ft_max(voxel->first->x, voxel->second->x);
	objet->ymax = ft_max(voxel->first->y, voxel->second->y);
}

void	ft_calcC(t_obj *objet, t_cam *cam)
{
	objet->xmin = cam->coord->x;
	objet->ymin = cam->coord->y;
	objet->xmax = cam->coord->x;
	objet->ymax = cam->coord->y;
}

void	ft_calccoordobjrt(t_rt *rt, t_obj *obj)
{
	printf("rtxmin=%i\nrtymin=%i\nrtxmax=%i\nrtymax=%i\n", rt->objxmin, rt->objymin, rt->objxmax, rt->objymax);
	printf("xmin=%i\nymin=%i\nxmax=%i\nymax=%i\n\n", obj->xmin, obj->ymin, obj->xmax, obj->ymax);
	if (obj->xmin < rt->objxmin)
		rt->objxmin = obj->xmin;
	if (obj->ymin < rt->objymin)
		rt->objymin = obj->ymin;
	if (obj->ymax > rt->objymax)
		rt->objymax = obj->ymax;
	if (obj->xmax > rt->objxmax)
		rt->objxmax = obj->xmax;
}

void	*ft_makeobj(t_rt *rt, void *obj, int type)
{
	t_obj	*objet;

	objet = ft_malloc(sizeof(t_obj), rt->garbage);
	if (!obj)
		ft_exit(rt, "malloc error\n");
	if (type == SP)
		ft_calcsp(objet, (t_sp *)obj);
	else if (type == VOXEL)
		ft_calcvoxel(objet, (t_voxel *)obj);
	else if (type == PL)
		ft_calcpl(objet, (t_pl *)obj);
	else if (type == C)
		ft_calcC(objet, (t_cam *)obj);
	objet->type = type;
	objet->obj = obj;
	ft_calccoordobjrt(rt, objet);
	return (objet);
}

void	*ft_makeseg(t_rt *rt, char *str)
{
	t_seg	*seg;
	int		i;
	int		color;

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
	color = ft_atoi(&str[i]);
	seg->first->color = color;
	seg->second->color = color;
	seg->color = color;
	return (ft_makeobj(rt, seg, SEG));
}

void	*ft_makevoxel(t_rt *rt, char *str)
{
	t_voxel	*voxel;
	int		i;
	int		color;

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
	color = ft_atoi(&str[i]);
	voxel->first->color = color;
	voxel->second->color = color;
	voxel->color = color;
	return (ft_makeobj(rt, voxel, VOXEL));
}

void	*ft_makesp(t_rt *rt, char *str)
{
	t_sp	*sp;
	int		i;
	int		color;

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
	color = ft_atoi(&str[i]);
	sp->coord->color = color;
	sp->color = color;
	return (ft_makeobj(rt, sp, SP));
}

void	*ft_makepl(t_rt *rt, char *str)
{
	t_pl	*pl;
	int		i;
	int		color;

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
	color = ft_atoi(&str[i]);
	pl->coord->color = color;
	pl->color = color;
	return (ft_makeobj(rt, pl, PL));
}

void	*ft_makecam(t_rt *rt, char *str)
{
	t_cam	*cam;
	int		i;
	int		color;

	i = 0;
	cam = ft_malloc(sizeof(t_cam), rt->garbage);
	if (!cam)
		ft_exit(rt, "malloc error\n");
	while (str[i] == ' ')
		i++;
	cam->coord = ft_atoicoord(rt, &str[i]);
	rt->cam = cam;
	color = 999;
	cam->coord->color = color;
	cam->color = color;
	return (ft_makeobj(rt, cam, C));
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
	rt->win_ptr = 0;
	rt->mlx_ptr = 0;
	rt->objxmin = 200000000;
	rt->objxmax = -200000000;
	rt->objymin = 200000000;
	rt->objymax = -200000000;
	rt->xsize = 1400;
	rt->ysize = 1400;
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
