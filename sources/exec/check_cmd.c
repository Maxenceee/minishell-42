/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:29:45 by mgama             #+#    #+#             */
/*   Updated: 2023/11/09 14:31:10 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_empty(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}

int	is_dir(char *str)
{
	struct stat	f;

	if (lstat(str, &f) != 0)
		return (0);
	if (S_ISDIR(f.st_mode))
	{
		if (*str == '.')
			str++;
		if (*str == '.')
			str++;
		if (*str == '/')
			return (1);
	}
	return (0);
}
