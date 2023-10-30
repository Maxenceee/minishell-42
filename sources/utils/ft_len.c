/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_len.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 21:23:53 by mgama             #+#    #+#             */
/*   Updated: 2023/10/28 19:30:03 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	if (!str)
		return (count);
	while (str[count++])
		;
	return (count);
}

int	ft_tablen(char **str)
{
	size_t	count;

	count = -1;
	while (str[++count])
		;
	return (count);
}
