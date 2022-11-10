/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_posclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 22:11:43 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/07 18:37:18 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ft_posclear(t_pos *pos, int freee)
{
	if (pos != NULL)
	{
		while (*pos->size != 0)
			ft_lstdelone(pos->start, freee);
		if (freee == 2)
		{
			free(pos->size);
			free(pos);
		}
	}
}
