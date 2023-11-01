/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:07:23 by mgama             #+#    #+#             */
/*   Updated: 2023/11/01 14:11:18 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strtcpy(char *str, int len)
{
	char	*s;

	s = ft_calloc(len + 1, sizeof(char));
	if (!s)
		return (NULL);
	ft_strlcpy(s, str, len);
	s[len] = 0;
	return (s);
}
