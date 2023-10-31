/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 00:15:32 by mgama             #+#    #+#             */
/*   Updated: 2023/11/01 00:17:51 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strjoin_char(char *s, char c)
{
	char	*str;
	int		i;

	if (!s)
		s = (char *)ft_calloc(1, sizeof(char));
	if (!s)
		return (NULL);
	str = ft_calloc((ft_strlen(s) + 1 + 1),
			sizeof(char));
	if (!str)
		return (free(s), NULL);
	i = -1;
	while (s && s[++i] != '\0')
		str[i] = s[i];
	str[i++] = c;
	str[i] = '\0';
	free(s);
	return (str);
}
