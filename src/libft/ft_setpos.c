/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setpos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:38:33 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/07 18:36:24 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rt.h"

t_pos	*ft_setpos(t_pos *garbage)
{
	t_pos	*pos;
	int		size;

	if (size == 0)
		return (0);
	pos = ft_malloc(sizeof(*pos), garbage);
	if (pos == 0)
	{
		return (0);
	}
	pos->size = 0;
	pos->start = 0;
	return (pos);
}
