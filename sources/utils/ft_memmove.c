/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 18:12:36 by mgama             #+#    #+#             */
/*   Updated: 2023/11/08 23:25:42 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*d;
	const char	*s;
	char		*lasts;
	char		*lastd;

	d = dst;
	if (len == 0 || dst == src)
		return (dst);
	s = src;
	if (d < s)
		while (len--)
			*d++ = *s++;
	else
	{
		lasts = (char *)(s + (len - 1));
		lastd = (char *)(d + (len - 1));
		while (len--)
			*lastd-- = *lasts--;
	}
	return (dst);
}
