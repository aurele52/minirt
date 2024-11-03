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
# define TEST 2
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

/*liste*/

//
#endif
