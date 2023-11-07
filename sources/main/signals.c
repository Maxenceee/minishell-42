/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:11:39 by mgama             #+#    #+#             */
/*   Updated: 2023/11/07 17:39:30 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_g_signal_val(int flag)
{
	if (flag == EXIT_CODE)
		return ((g_signal << 24) >> 24);
	else if (flag == STOP_HEREDOC)
		return ((g_signal & flag) >> 8);
	else if (flag == IN_CMD)
		return ((g_signal & flag) >> 9);
	else if (flag == IN_HERE_DOC)
		return ((g_signal & flag) >> 10);
	return (0);
}

void	set_g_signal_val(int flag, int val)
{
	if (flag == EXIT_CODE)
		g_signal = ((g_signal >> 8) << 8) | val;
	else if (flag == STOP_HEREDOC)
	{
		g_signal &= ~(1 << 8);
		g_signal |= val << 8;
	}
	else if (flag == IN_CMD)
	{
		g_signal &= ~(1 << 9);
		g_signal |= val << 9;
	}
	else if (flag == IN_HERE_DOC)
	{
		g_signal &= ~(1 << 10);
		g_signal |= val << 10;	
	}
}

int	event(void)
{
	return (MS_SUCCESS);
}

void	sigint_handler(int sig)
{
	(void)sig;
	if (!get_g_signal_val(IN_HERE_DOC))
		ft_putfd(STDERR_FILENO, "\n");
	if (get_g_signal_val(IN_CMD))
	{
		set_g_signal_val(EXIT_CODE, 130);
		set_g_signal_val(STOP_HEREDOC, 1);
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
