/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffreze <ffreze@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:53:11 by mgama             #+#    #+#             */
/*   Updated: 2023/11/03 18:32:23 by ffreze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execcmd(char **command, t_data *ms)
{
	char		*cmd;
	char		**envp;

	// envp = dup_env(ms);
	envp = ms->envp;
	if (command[0] == NULL)
		return (5);
	cmd = parse_env(ms, command[0]);
	if (!cmd || ft_strcmp(command[0], "") == 0)
		return (2);
	if (execve(cmd, command, envp) == -1)
		return (perror(MS_EXEVE_ERROR), MS_ERROR);
	return (MS_NO_ERROR);
}

int	open_fdinout(t_parsing_cmd *cmd)
{
	t_parsing_file	*f;

	f = cmd->files;
	while (f)
	{
		f->fd = open(f->file_name, O_CREAT | cmd->files->type | O_WRONLY, 0644);
		f = f->next;
	}
	return (MS_SUCCESS);
}

int	dup_cmd(t_data *minishell, t_parsing_cmd *cmd)
{
	if (cmd->prev && dup2(cmd->fin, STDIN_FILENO) < 0)
		return (MS_ERROR);
	close(cmd->pipe[0]);
	if (cmd->next && dup2(cmd->pipe[1], STDOUT_FILENO) < 0)
		return (MS_ERROR);
	close(cmd->pipe[1]);
	if (cmd->prev)
		close(cmd->fin);
	execcmd(cmd->cmd, minishell);
	// if (res == 5)
	// 	return (MS_ERROR);
	// else if (res == 2)
	// {
	// 	ft_error(MS_COMMAND_NOT_FOUND);
	// 	ft_error(cmd->cmd[0]);
	// 	ft_error("\n");
	// }
}

int	process_child(t_data *minishell, t_parsing_cmd *cmd)
{
	int		res;

	cmd->pid = fork();
	if (cmd->pid == -1)
		return (MS_ERROR);
	if (cmd->pid == 0)
	{
		if (dup_cmd(minishell, cmd))
			return (MS_ERROR);
	}
	if (cmd->next)
		return (MS_SUCCESS);
	return (MS_SUCCESS);
}

int	fork_processes(t_data *minishell)
{
	t_parsing_cmd	*cmd;

	cmd = minishell->parsing_cmd;
	while (cmd)
	{
		cmd->fin = STDIN_FILENO;
		if (cmd->next)
			if (pipe(cmd->pipe) == -1)
				return (MS_ERROR);
		if (process_child(minishell, cmd))
			return (MS_ERROR);
		close(cmd->pipe[1]);
		if (cmd->prev)
			close(cmd->fin);
		// heredoc
		cmd = cmd->next;
	}
	return (MS_SUCCESS);
}

int	mini_exec(t_data *minishell)
{
	if (fork_processes(minishell))
		return (MS_ERROR);
	return (MS_SUCCESS);
}
