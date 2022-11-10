/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:22:31 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/09 18:14:49 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# define ZLIMITE 0.1
# define BUFFER_SIZE 2000
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pos
{
	struct s_list	*start;
	struct s_list	*end;
	int				*size;
}	t_pos;

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*back;
	void			*content;
	struct s_pos	*pos;
}	t_list;

typedef struct s_coord
{
	int	x;
	int	y;
	int	color;
}	t_coord;

typedef struct s_ori
{
	int	x;
	int	y;
}	t_ori;

typedef struct s_cam
{
	t_coord	*coord;
	int		color;
}	t_cam;

typedef struct s_sp
{
	t_coord	*coord;
	int	rayon;
	int	color;
}	t_sp;

typedef struct s_pl
{
	t_coord	*coord;
	t_ori	*ori;
	int	color;
}	t_pl;

typedef struct s_seg
{
	t_coord	*first;
	t_coord	*second;
	int	color;
}	t_seg;

typedef struct s_voxel
{
	t_coord	*first;
	t_coord	*second;
	int	color;
}	t_voxel;

enum e_objtype
{
	VOXEL,
	SP,
	PL,
	C,
	SEG
};

typedef struct s_binarytree
{
	t_pos	*obj;
	struct s_binarytree *par;
	struct s_binarytree *av;
	struct s_binarytree *ar;
}	t_binarytree;

typedef struct s_obj
{
	int		type;
	void	*obj;
	int		xmin;
	int		ymin;
	int		xmax;
	int		ymax;
}	t_obj;

typedef struct s_imginfo
{
	void	*origin;
	char	*imgaddress;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_imginfo;

typedef struct s_rt
{
	t_imginfo	image;
	t_pos		*garbage;
	void		*win_ptr;
	void		*mlx_ptr;
	int			xsize;
	int			ysize;
	int			objxmin;
	int			objymin;
	int			objxmax;
	int			objymax;
	t_cam		*cam;
	t_pos		*obj;
}	t_rt;

/*liste*/

t_pos		*ft_setpos(t_pos *garbage);
void		ft_lstdelone(t_list *lst, int garbage);
t_list		*ft_lstnew(void *content, t_pos *pos, t_pos *garbage);
void		ft_posclear(t_pos *pos, int garbage);
void		ft_posprint(t_rt *rt, t_pos *pos, void (*fct)(t_rt *, void *, int), int fd);

/*cast*/

t_cam	*ft_C(t_list *liste);
t_pl	*ft_pl(t_list *liste);
t_seg	*ft_seg(t_list *liste);
t_voxel	*ft_voxel(t_list *liste);
t_sp	*ft_sp(t_list *liste);
int		ft_type(t_list *liste);

/*droite*/

void	ft_printsamey(t_rt *rt, t_coord one, t_coord two);
void	ft_printdiagonefour(t_rt *rt, t_coord one, t_coord two);
void	ft_printdiagtwothree(t_rt *rt, t_coord one, t_coord two);
void	ft_printdiag(t_rt *rt, t_coord one, t_coord two);
void	ft_printsamex(t_rt *rt, t_coord one, t_coord two);
void	ft_printdroite(t_rt *rt, t_coord one, t_coord two);
void	ft_bresenhamoneeight(t_rt *rt, t_coord one, t_coord two);

/*utils*/

void	ft_swapcoord(t_coord *a, t_coord *b);
void	ft_swap(int *a, int *b);
void	ft_printpixelimg(t_rt *rt, t_coord *print);
t_coord	*ft_makecoord(t_rt *rt, int x, int y, int color);

/*Sphere*/

void	ft_printsp(t_rt *rt, t_sp *sp);

/*libft*/

char		*get_next_line(int fd, t_pos *free);
int			ft_abs(int nbr);
void		ft_exit(t_rt *rt, char *str);
int			ft_closevaria(int i, ...);
char		*ft_strjoin(char *s1, char *s2, t_pos *garbage);
void		ft_putnbrfd(int n, int fd);
char		*ft_strdup(const char *s, t_pos *garbage);
char		*ft_substr(char const *s, int start, int len, t_pos *garb);
int			ft_strcmp(const char *str1, const char *str2);
void		*ft_malloc(int size, t_pos *garbage);
int			ft_strlen(const char *s);
char		**ft_split(char const *s, char c, t_pos *garbage);
char		*ft_itoa(int n, t_pos *garbage);
int			ft_atoi(char *str);
int			ft_doublstrlen(char **str);
int			ft_max(int nb1, int nb2);
int			ft_min(int nb1, int nb2);

#endif
