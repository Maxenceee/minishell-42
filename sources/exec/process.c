/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:53:11 by mgama             #+#    #+#             */
/*   Updated: 2023/11/08 01:23:29 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_child(t_data *minishell, t_parsing_cmd *cmd, int pip[2])
{
	cmd->pid = fork();
	setup_exec_signals(cmd->pid);
	if (cmd->pid == -1)
		return (MS_ERROR);
	if (cmd->pid == 0)
	{
		if (dup_cmd(minishell, cmd, pip))
			return (MS_ERROR);
	}
	if (cmd->next)
		return (MS_SUCCESS);
	return (MS_SUCCESS);
}

void	process_wait(t_data *ms)
{
	int				status;
	t_parsing_cmd	*cmd;

	cmd = ms->parsing_cmd;
	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		cmd = cmd->next;
	}
	if (WIFEXITED(status))
		set_g_signal_val(EXIT_CODE, WEXITSTATUS(status));
}

int	fork_processes(t_data *minishell)
{
	int				hd_sts;
	int				fin;
	int				pip[2];
	t_parsing_cmd	*cmd;

	fin = STDIN_FILENO;
	cmd = minishell->parsing_cmd;
	while (cmd)
	{
		cmd->fin = fin;
		if (cmd->next)
			if (pipe(pip) == -1)
				return (MS_ERROR);
		hd_sts = open_heredoc(minishell, cmd);
		if (hd_sts == MS_ERROR)
			return (MS_ERROR);
		else if (hd_sts)
			return (MS_SUCCESS);
		if (process_child(minishell, cmd, pip))
			return (MS_ERROR);
		if (cmd->next)
			close(pip[1]);
		if (cmd->prev)
			close(cmd->fin);
		fin = check_fd_heredoc(cmd, pip);
		cmd = cmd->next;
	}
	process_wait(minishell);
	return (MS_SUCCESS);
}

void	fork_single(t_data *minishell, t_parsing_cmd *cmd)
{
	int	hd_sts;
	int	status;

	if (cmd->builtin && is_builtin_no_out(cmd))
	{
		set_g_signal_val(EXIT_CODE, cmd->builtin(minishell, cmd));
		return ;
	}
	hd_sts = open_heredoc(minishell, cmd);
	if (hd_sts)
		return ;
	cmd->pid = fork();
	setup_exec_signals(cmd->pid);
	if (cmd->pid == -1)
		exit_with_code(minishell, MS_ERROR, NULL);
	if (cmd->pid == 0)
		handle_cmd(minishell, cmd);
	waitpid(cmd->pid, &status, 0);
	if (WIFEXITED(status))
		set_g_signal_val(EXIT_CODE, WEXITSTATUS(status));
}

int	mini_exec(t_data *minishell)
{
	if (!minishell->parsing_cmd)
		return (MS_ERROR);
	// signal(SIGQUIT, sigquit_handler);
	set_g_signal_val(IN_CMD, 1);
	if (!minishell->parsing_cmd->next)
		fork_single(minishell, minishell->parsing_cmd);
	else if (fork_processes(minishell))
		return (MS_ERROR);
	set_g_signal_val(IN_CMD, 0);
	return (MS_SUCCESS);
}
