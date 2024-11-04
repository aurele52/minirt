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
// # define ZLIMITE 0.1
# define BUFFER_SIZE 20000
# define TEST 1
#define STEP 1
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

typedef double t_coord __attribute__((ext_vector_type(2)));

typedef struct s_pos
{
	struct s_list	*start;
	struct s_list	*end;
	int				size;
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

typedef struct s_lycee
{
	t_color	color;
	t_coord	coord;
	double	rayon;
	double value;
	char *name;
}	t_lycee;

typedef struct s_line
{
	t_color	color;
	t_coord	coord;
	t_coord	ori;
}	t_line;

typedef struct s_seg
{
	t_color	color;
	t_coord	first;
	t_coord	second;
}	t_seg;

typedef struct s_square
{
	t_color	color;
	t_coord	first;
	t_coord	second;
}	t_square;


enum e_objtype
{
	SQUARE,
	LYCEE,
	SEG
	// L,
};

typedef struct s_bt
{
	t_pos	*obj;
	struct s_bt *racine;
	struct s_bt *left;
	struct s_bt *right;
	struct s_line *split;
}	t_bt;

// typedef struct s_bt
// {
// 	t_pos	*obj;
// 	struct s_bt *racine;
// 	struct s_bt *left;
// 	struct s_bt *right;
// }	t_bt;

typedef struct s_obj
{
	int		type;
	void	*obj;
	double		xmin;
	double		ymin;
	double		xmax;
	double		ymax;
}	t_obj;

typedef struct s_imginfo
{
	void	*origin;
	char	*imgaddress;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_imginfo;

typedef struct s_scene
{
	t_pos		garbage;
	double		objxmin;
	double		objymin;
	double		objxmax;
	double		objymax;
	t_pos		obj;
	t_bt		*tree;
}	t_scene;


typedef struct s_rt
{
	t_pos		garbage;
	t_imginfo	image;
	void		*win_ptr;
	void		*mlx_ptr;
	int			xsize;
	int			ysize;
	t_coord		origin;
	t_scene		scene;
}	t_rt;


/*Tree*/
void makeTree(t_rt *rt);

/*Parse*/
void	ft_open(t_rt *rt, t_coord coord);

/*Cast*/
t_lycee	*listToLycee(t_list *liste);
int	colorToInt(t_color *color);
t_color	intToColor(int color);
int		listeToType(t_list *liste);


/*Print*/
void	printdroite(t_rt *rt, t_coord one, t_coord two, t_color color);
void	printLycee(t_rt *rt, t_lycee *sp);
void	printseg(t_rt *rt, t_seg *seg);
void	printdroite(t_rt *rt, t_coord one, t_coord two, t_color color);
void	printSquare(t_rt *rt, t_square *square);
void	printobj(t_rt *rt, t_obj *obj);






/*utils*/
t_coord	makecoord(t_rt *rt, double x, double y);
char		*get_next_line(int fd, t_pos *free);
int			ft_abs(int nbr);
void		ft_exit(t_rt *rt, char *str);
char		*strjoin(char *s1, char *s2, t_pos *garbage);
void		putnbrfd(int n, int fd);
char		*ft_strdup(const char *s, t_pos *garbage);
char		*substr(char const *s, int start, int len, t_pos *garb);
void		*ft_malloc(int size, t_pos *garbage);
char		**split(char const *s, char c, t_pos *garbage);
char		*itoa(int n, t_pos *garbage);
int			atoi(const char *str);
int			max(int nb1, int nb2);
int			min(int nb1, int nb2);
int	ft_strstr(const char *big, const char *libtle);
t_pos		*setpos(t_pos *garbage);
void		lstdelone(t_list *lst, int garbage);
t_list		*lstnew(void *content, t_pos *pos, t_pos *garbage);
void		posclear(t_pos *pos, int garbage);
void		posprint(t_rt *rt, t_pos *pos, void (*fct)(t_rt *, void *, int), int fd);

#endif
