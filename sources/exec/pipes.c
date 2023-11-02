/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:21:50 by mgama             #+#    #+#             */
/*   Updated: 2023/11/02 02:44:20 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipes(t_parsing_cmd *cmd)
{
	t_parsing_file	*f;

	close(cmd->pipe[0]);
	close(cmd->pipe[1]);
	f = cmd->files;
	while (f)
	{
		if (f->fd >= 0)
			close(f->fd);
		f = f->next;
	}
}

int	dup2_fdinout(int fdin, int fdout)
{
	if (dup2(fdin, STDIN_FILENO) < 0)
		return (3);
	if (dup2(fdout, STDOUT_FILENO) < 0)
		return (3);
	return (0);
}
