/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_contains.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:25:12 by mgama             #+#    #+#             */
/*   Updated: 2023/11/12 19:34:55 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_contains(char *line, char check)
{
	int	i;
	int	j;

	if (!line)
		return (0);
	i = -1;
	j = 0;
	while (line[++i])
	{
		if (line[i] == check)
			j++;
	}
	return (j);
}
