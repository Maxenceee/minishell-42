/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:11:39 by mgama             #+#    #+#             */
/*   Updated: 2023/11/04 00:40:19 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	event(void)
{
	return (MS_SUCCESS);
}

void	sigint_handler(int sig)
{
	(void)sig;
	if (!g_signal.in_here_doc)
		write(STDERR_FILENO, "\n", 1);
	if (g_signal.in_cmd)
	{
		g_signal.stop_heredoc = 1;
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		return ;
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	(void) sig;
}

void	sigquit_handler(int sig)
{
	write(STDERR_FILENO, "Quit: ", 7);
	ft_putnbr_fd(STDERR_FILENO, sig);
	write(STDERR_FILENO, "\n", 1);
}

void	setup_signals(void)
{
	rl_event_hook = event;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
