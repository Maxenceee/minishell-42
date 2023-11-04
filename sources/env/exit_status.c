/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 01:43:27 by mgama             #+#    #+#             */
/*   Updated: 2023/11/04 01:49:38 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exit_status(char *line)
{
	char	*res;
	char	*tmp;

	tmp = ft_itoa(g_signal.exit_code);
	res = ft_strjoin(line, tmp);
	free(tmp);
	return (res);
}
