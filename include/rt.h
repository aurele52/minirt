/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 19:22:31 by audreyer          #+#    #+#             */
/*   Updated: 2023/01/10 16:44:38 by audreyer         ###   ########.fr       */
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
# include <limits.h>
# include <float.h>
# include <unistd.h>
# include <stdio.h>
# include <stdarg.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdbool.h>

typedef float t_coord __attribute__((ext_vector_type(3)));

typedef struct s_pos
{
	struct s_list	*start;
	struct s_list	*end;
	int				*size;
}	t_pos;

typedef struct s_color
{
	int	red;
	int	blue;
	int	green;
}	t_color;

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*back;
	void			*content;
	struct s_pos	*pos;
}	t_list;

typedef struct	s_cam
{
	bool	yes;
	t_coord	coord;
	t_coord	ori;
	t_coord	bottom_left;
	t_coord	right;
	t_coord	up;
	t_color	color;
	int		fov;
}				t_cam;

typedef struct	s_rotation
{
	float	yaw;
	float	pitch;
	float	roll;
}				t_rotation;

typedef struct s_sp
{
	t_color	color;
	t_coord	coord;
	float	rayon;
}	t_sp;

typedef struct s_pl
{
	t_color	color;
	t_coord	coord;
	t_coord	ori;
}	t_pl;

typedef struct s_ray
{
	t_color	color;
	t_coord	coord;
	t_coord	ori;
	t_coord	through;
}	t_ray;

typedef struct s_seg
{
	t_color	color;
	t_coord	first;
	t_coord	second;
}	t_seg;

typedef struct s_voxel
{
	t_color	color;
	t_coord	first;
	t_coord	second;
}	t_voxel;

typedef struct s_light
{
	t_color	color;
	t_coord	coord;
	float	intensiter;
	bool	yes;
}	t_light;

enum e_objtype
{
	VOXEL,
	SP,
	PL,
	C,
	L,
	SEG
};

typedef struct s_bt
{
	t_pos	*obj;
	struct s_bt *racine;
	struct s_bt *left;
	struct s_bt *right;
}	t_bt;

typedef struct s_obj
{
	int		type;
	void	*obj;
	float		xmin;
	float		ymin;
	float		xmax;
	float		ymax;
	float		zmin;
	float		zmax;
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
	float		objxmin;
	float		objymin;
	float		objzmin;
	float		objzmax;
	float		objxmax;
	float		objymax;
	float		fov;
	t_color		color;
	t_coord		origin;
	t_cam		cam;
	t_light		light;
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

void	ft_printsamey(t_rt *rt, t_coord one, t_coord two, t_color color);
void	ft_printdiagonefour(t_rt *rt, t_coord one, t_coord two, t_color color);
void	ft_printdiagtwothree(t_rt *rt, t_coord one, t_coord two, t_color color);
void	ft_printdiag(t_rt *rt, t_coord one, t_coord two, t_color color);
void	ft_printsamex(t_rt *rt, t_coord one, t_coord two, t_color color);
void	ft_printdroite(t_rt *rt, t_coord one, t_coord two, t_color color);
void	ft_bresenhamoneeight(t_rt *rt, t_coord one, t_coord two, t_color color);

/*utils*/

void	ft_swapcoord(t_coord *a, t_coord *b);
void	ft_swap(float *a, float *b);
void	ft_printpixelimg(t_rt *rt, t_coord print, t_color color);
t_coord	ft_makecoord(t_rt *rt, float x, float y, float z);

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
