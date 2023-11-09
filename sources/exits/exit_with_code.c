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

int	exit_with_error(t_data *ms, int error_code, char *message)
{
	free_minishell(ms);
	if (message)
		ft_error(MS_ERROR_PREFIX, message);
	exit(error_code);
	return (MS_ERROR);
}

void	ft_cmderror(char *cmd, char *msg)
{
	write(STDERR_FILENO, MS_ERROR_PREFIX, ft_strlen(MS_ERROR_PREFIX));
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, msg, ft_strlen(msg));
}

void	ft_cmderror_ex(char *head, char *cmd, char *msg)
{
	write(STDERR_FILENO, MS_ERROR_PREFIX, ft_strlen(MS_ERROR_PREFIX));
	write(STDERR_FILENO, head, ft_strlen(head));
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, msg, ft_strlen(msg));
}
