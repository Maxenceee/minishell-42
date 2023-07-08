/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:57:06 by mgama             #+#    #+#             */
/*   Updated: 2023/07/07 19:01:42 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_data *minishell)
{
	close(minishell->fdin);
	close(minishell->fdout);
	close(minishell->pipein);
	close(minishell->pipeout);
}

void	reset_fds(t_data *minishell)
{
	minishell->fdin = -1;
	minishell->fdout = -1;
	minishell->pipein = -1;
	minishell->pipeout = -1;
	minishell->pid = -1;
}