/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 19:11:39 by mgama             #+#    #+#             */
/*   Updated: 2023/11/08 01:23:45 by mgama            ###   ########.fr       */
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

// int	event(void)
// {
// 	return (MS_SUCCESS);
// }

// void	sigint_handler(int sig)
// {
// 	(void)sig;
// 	if (!get_g_signal_val(IN_HERE_DOC))
// 		ft_putfd(STDERR_FILENO, "\n");
// 	if (get_g_signal_val(IN_CMD))
// 	{
// 		set_g_signal_val(EXIT_CODE, 130);
// 		set_g_signal_val(STOP_HEREDOC, 1);
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 		rl_done = 1;
// 		return ;
// 	}
// 	rl_on_new_line();
// 	rl_replace_line("", 0);
// 	rl_redisplay();
// }

// void	sigquit_handler(int sig)
// {
// 	ft_putfd(STDERR_FILENO, "Quit: ");
// 	ft_putnbr_fd(STDERR_FILENO, sig);
// 	ft_putfd(STDERR_FILENO, "\n");
// }

// void	setup_signals(void)
// {
// 	rl_event_hook = event;
// 	signal(SIGINT, sigint_handler);
// 	signal(SIGQUIT, SIG_IGN);
// }

void	handle_sigint(int sig)
{
	(void)sig;
	ft_putfd(STDOUT_FILENO, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_signals(void)
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	sa_sigint.sa_handler = &handle_sigint;
	sa_sigint.sa_flags = 0;
	sigemptyset(&sa_sigint.sa_mask);
	sigaction(SIGINT, &sa_sigint, NULL);
	sa_sigquit.sa_handler = SIG_IGN;
	sa_sigquit.sa_flags = 0;
	sigemptyset(&sa_sigquit.sa_mask);
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}

void	setup_exec_signals(int child_pid)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (child_pid == 0)
		sa.sa_handler = SIG_DFL;
	else
		sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	setup_hd_signals(int child_pid)
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	sa_sigint.sa_flags = 0;
	sigemptyset(&sa_sigint.sa_mask);
	if (child_pid == 0)
		sa_sigint.sa_handler = SIG_DFL;
	else
		sa_sigint.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa_sigint, NULL);
	sa_sigquit.sa_flags = 0;
	sigemptyset(&sa_sigquit.sa_mask);
	sa_sigquit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}
