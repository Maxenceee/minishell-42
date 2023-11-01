/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:53:11 by mgama             #+#    #+#             */
/*   Updated: 2023/11/01 19:53:13 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execcmd(char **command, t_data *ms)
{
	char		*cmd;
	char		**envp;

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
		if (f->next)
			f->fd = open(f->file_name, O_CREAT);
		else
		{
			if (cmd->type == REDIR_OUT)
				f->fd = open(f->file_name, O_TRUNC);
			else
				f->fd = open(f->file_name, O_APPEND);
		}
		// printf("name %s, fd=%d\n", f->file_name, f->fd);
		f = f->next;
	}
	if (pipe(cmd->pipe) == -1)
		return (MS_ERROR);
	// printf("pipe read %d write %d\n", cmd->pipe[0], cmd->pipe[1]);
	return (MS_SUCCESS);
}

int	process_child(t_data *minishell, t_parsing_cmd *cmd)
{
	pid_t	pid;
	int		res;

	pid = fork();
	if (pid == -1)
		return (MS_ERROR);
	if (pid == 0)
	{
		res = execcmd(cmd->cmd, minishell);
		if (res == 5)
			return (MS_ERROR);
		else if (res == 2)
		{
			ft_error(MS_COMMAND_NOT_FOUND);
			ft_error(cmd->cmd[0]);
			ft_error("\n");
		}
		close_pipes(cmd);
		exit(1);
	}
}

int	fork_processes(t_data *minishell)
{
	t_parsing_cmd	*cmd;
	t_parsing_cmd	*last;
	int				fd[2];

	cmd = minishell->parsing_cmd;
	while (cmd)
	{
		if (open_fdinout(cmd))
			return (MS_ERROR);
		cmd = cmd->next;
	}
	cmd = minishell->parsing_cmd;
	last = NULL;
	while (cmd)
	{
		fd[0] = 0;
		fd[1] = 1;
		if (last)
			fd[0] = last->pipe[0];
		if (cmd->next)
			fd[1] = last->pipe[1];
		if (dup2_fdinout(fd[0], fd[1]))
			return (MS_ERROR);
		last = cmd;
		cmd = cmd->next;
	}
	cmd = minishell->parsing_cmd;
	while (cmd)
	{
		process_child(minishell, cmd);
		cmd = cmd->next;
	}
	waitpid(-1, NULL, 0);
	return (MS_NO_ERROR);
}
