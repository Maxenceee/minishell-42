/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 21:23:49 by mgama             #+#    #+#             */
/*   Updated: 2023/11/02 15:18:44 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static int	ft_str_length(char *str)
{
	int	index;

	index = 0;
	while (str[index])
		index++;
	return (index);
}

static char	*ft_strcpy(char *dest, char *src)
{
	int	index;

	index = 0;
	while (src[index] != '\0')
	{
		dest[index] = src[index];
		index++;
	}
	dest[index] = '\0';
	return (dest);
}

static int	ft_compute_final_length(char **strings, int size, int sep_length)
{
	int	final_length;
	int	index;

	final_length = 0;
	index = 0;
	while (index < size)
	{
		final_length += ft_str_length(strings[index]);
		final_length += sep_length;
		index++;
	}
	final_length -= sep_length;
	return (final_length);
}

char	*ft_strjoin_arr(int size, char **strs, char *sep)
{
	int		full_length;
	int		index;
	char	*string;
	char	*d;

	if (size == 0)
		return ((char *)malloc(sizeof(char)));
	full_length = ft_compute_final_length(strs, size, ft_str_length(sep));
	string = (char *)malloc((full_length + 1) * sizeof(char));
	d = (string);
	if (!d)
		return (0);
	index = -1;
	while (++index < size)
	{
		ft_strcpy(d, strs[index]);
		d += ft_str_length(strs[index]);
		if (index < size - 1)
		{
			ft_strcpy(d, sep);
			d += ft_str_length(sep);
		}
	}
	*d = '\0';
	return (string);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1)
		s1 = (char *)ft_calloc(1, sizeof(char));
	if (!s1)
		return (NULL);
	if (!s2)
		return (free(s1), NULL);
	str = ft_calloc((ft_strlen(s1) + ft_strlen(s2) + 1),
			sizeof(char));
	if (!str)
		return (free(s1), NULL);
	i = -1;
	j = 0;
	while (s1 && s1[++i] != '\0')
		str[i] = s1[i];
	while (s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}
