/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strequal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 13:50:12 by mgama             #+#    #+#             */
/*   Updated: 2024/01/14 13:50:21 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	str_equal(const char *str1, const char *str2)
{
	size_t	size;

	if (!str1 || !str2)
		return (0);
	size = ft_strlen(str1);
	if (size != ft_strlen(str2))
		return (0);
	return (ft_strncmp(str1, str2, size) == 0);
}
