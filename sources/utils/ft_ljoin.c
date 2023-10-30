/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ljoin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 15:49:53 by mgama             #+#    #+#             */
/*   Updated: 2023/10/26 15:54:06 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_ljoin(void *s1, void *s2,
	unsigned int size, unsigned int length)
{
	void	*str;
	int		i;
	int		j;

	if (!s1)
		s1 = (void *)ft_calloc(1, sizeof(void *));
	if (!s1)
		return (NULL);
	if (!s2)
		return (free(s1), NULL);
	str = malloc(
			sizeof(void) * (size + length + 1));
	if (!str)
		return (free(s1), NULL);
	i = -1;
	j = -1;
	while (++i < size)
		ft_memcpy(str + i, s1 + i, sizeof(void *));
	while (++j < length)
		ft_memcpy(str + i++, s1 + j, sizeof(void *));
	free(s1);
	return (str);
}
