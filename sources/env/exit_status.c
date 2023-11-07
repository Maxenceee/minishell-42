/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 01:43:27 by mgama             #+#    #+#             */
/*   Updated: 2023/11/07 17:14:33 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exit_status(char *line)
{
	char	*res;
	char	*tmp;

	tmp = ft_itoa(get_g_signal_val(EXIT_CODE));
	res = ft_strjoin(line, tmp);
	free(tmp);
	return (res);
}
