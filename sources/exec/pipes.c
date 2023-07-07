/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:21:50 by mgama             #+#    #+#             */
/*   Updated: 2023/07/07 18:37:21 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	create_pipes(t_data *commands)
{
	int	i;

	i = -1;
	while (++i < commands->process_count)
	{
		if (pipe(commands->pipes + 2 * i) == -1)
			exit_error_with_msg(commands, PIPE_ERROR);
	}
}

void	close_pipes(t_data *commands)
{
	int	i;

	i = -1;
	while (++i < commands->pipe_nb)
		close(commands->pipes[i]);
}

int	dup2_fdinout(int fdin, int fdout)
{
	if (dup2(fdin, STDIN_FILENO) < 0)
		return (3);
	if (dup2(fdout, STDOUT_FILENO) < 0)
		return (3);
	return (0);
}
