/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:11:39 by mgama             #+#    #+#             */
/*   Updated: 2023/11/04 03:05:27 by mgama            ###   ########.fr       */
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
		ft_putfd(STDERR_FILENO, "\n");
	if (g_signal.in_cmd)
	{
		g_signal.exit_code = 130;
		g_signal.stop_heredoc = 1;
		rl_replace_line("", 0);
		rl_redisplay();
		rl_done = 1;
		return ;
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sigquit_handler(int sig)
{
	ft_putfd(STDERR_FILENO, "Quit: ");
	ft_putnbr_fd(STDERR_FILENO, sig);
	ft_putfd(STDERR_FILENO, "\n");
}

void	setup_signals(void)
{
	rl_event_hook = event;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}
