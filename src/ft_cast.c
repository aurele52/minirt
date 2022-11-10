/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:59:48 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/09 18:14:00 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_cam	*ft_C(t_list *liste)
{
	t_obj	*obj;
	t_cam	*cam;

	obj = (t_obj *)liste->content;
	cam = (t_cam *)obj->obj;
	return (cam);
}

t_sp	*ft_sp(t_list *liste)
{
	t_obj	*obj;
	t_sp	*sp;

	obj = (t_obj *)liste->content;
	sp = (t_sp *)obj->obj;
	return (sp);
}

t_pl	*ft_pl(t_list *liste)
{
	t_obj	*obj;
	t_pl	*pl;

	obj = (t_obj *)liste->content;
	pl = (t_pl *)obj->obj;
	return (pl);
}

t_voxel	*ft_voxel(t_list *liste)
{
	t_obj	*obj;
	t_voxel	*voxel;

	obj = (t_obj *)liste->content;
	voxel = (t_voxel *)obj->obj;
	return (voxel);
}

t_seg	*ft_seg(t_list *liste)
{
	t_obj	*obj;
	t_seg	*seg;

	obj = (t_obj *)liste->content;
	seg = (t_seg *)obj->obj;
	return (seg);
}

int	ft_type(t_list *liste)
{
	t_obj	*obj;

	obj = liste->content;
	return (obj->type);
}
