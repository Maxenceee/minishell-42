/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:53:11 by mgama             #+#    #+#             */
/*   Updated: 2023/12/19 12:49:35 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_child(t_data *minishell, t_parsing_cmd *cmd, int pip[2])
{
	cmd->pid = fork();
	setup_exec_signals(cmd->pid);
	if (cmd->pid == -1)
		exit_with_error(minishell, MS_ERROR, MS_FORK_ERROR);
	if (cmd->pid == 0)
	{
		if (dup_cmd(minishell, cmd, pip))
			return (MS_ERROR);
	}
	if (cmd->next)
		return (MS_SUCCESS);
	return (MS_SUCCESS);
}

int	process_child(t_data *minishell, t_parsing_cmd *cmd, int pip[2])
{
	int				hd_sts;

	hd_sts = open_heredoc(minishell, cmd);
	if (hd_sts)
		return (hd_sts);
	if (exec_child(minishell, cmd, pip))
		return (MS_ERROR);
	if (cmd->next)
		close(pip[1]);
	if (cmd->prev)
		close(cmd->fin);
	return (MS_SUCCESS);
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
		hd_sts = process_child(minishell, cmd, pip);
		if (hd_sts == MS_ERROR)
			return (MS_ERROR);
		else if (hd_sts)
			return (MS_SUCCESS);
		fin = check_fd_heredoc(cmd, pip);
		cmd = cmd->next;
	}
	wait_all_process(minishell);
	return (MS_SUCCESS);
}

int	fork_single(t_data *minishell, t_parsing_cmd *cmd)
{
	int	hd_sts;

	if (cmd->builtin && is_builtin_no_out(cmd))
	{
		set_g_signal_val(EXIT_CODE, cmd->builtin(minishell, cmd));
		return (MS_SUCCESS);
	}
	hd_sts = open_heredoc(minishell, cmd);
	if (hd_sts)
		return (MS_ERROR);
	dprintf(2, "after here doc\n");
	fflush(stderr);
	cmd->pid = fork();
	setup_exec_signals(cmd->pid);
	if (cmd->pid == -1)
		exit_with_error(minishell, MS_ERROR, MS_FORK_ERROR);
	if (cmd->pid == 0)
		handle_cmd(minishell, cmd);
	else
		return (wait_process(cmd->pid, 1));
	exit(MS_ERROR);
}

int	mini_exec(t_data *minishell)
{
	if (!minishell->parsing_cmd)
		return (MS_ERROR);
	if (!minishell->parsing_cmd->next)
		fork_single(minishell, minishell->parsing_cmd);
	else if (fork_processes(minishell))
		return (MS_ERROR);
	return (MS_SUCCESS);
}
