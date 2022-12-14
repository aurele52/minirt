/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:30:34 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/07 18:36:02 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*ft_strjoin(char *s1, char *s2, t_pos *garb)
{
	char	*str;
	int		i;
	int		j;

	i = -1;
	j = 0;
	str = ft_malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1), garb);
	if (!(str))
		return (0);
	while (s1[++i])
		str[i] = s1[i];
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = 0;
	return (str);
}
