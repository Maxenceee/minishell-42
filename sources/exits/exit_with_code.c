/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_with_code.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 01:52:30 by mgama             #+#    #+#             */
/*   Updated: 2023/11/04 01:56:03 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_with_code(t_data *ms, int error_code, char *message)
{
	free_minishell(ms);
	if (message && error_code == 0)
		printf("%s", message);
	else if (message)
		ft_putfd(STDERR_FILENO, message);
	exit(error_code);
}

void	exit_with_error(t_data *ms, int error_code, char *message)
{
	free_minishell(ms);
	if (message)
		ft_error(message);
	exit(error_code);
}
