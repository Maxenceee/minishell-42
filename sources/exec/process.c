/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:53:11 by mgama             #+#    #+#             */
/*   Updated: 2023/11/02 14:52:01 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execcmd(char **command, t_data *ms)
{
	char		*cmd;
	char		**envp;

	envp = dup_env(ms);
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
	cmd->fin = STDIN_FILENO;
	cmd->fout = STDOUT_FILENO;
	while (f)
	{
		if (f->next)
			f->fd = open(f->file_name, O_CREAT);
		else
		{
			f->fd = open(f->file_name, O_CREAT | cmd->type | O_WRONLY, 0644);
			cmd->fout = f->fd;
		}
		printf("%s %d\n", f->file_name, f->fd);
		if (f->fd == -1)
			return (ft_error(MS_OPEN_ERROR), ft_error(f->file_name),
				ft_error("\n"), MS_ERROR);
		f = f->next;
	}
	if (pipe(cmd->pipe) == -1)
		return (ft_error(MS_PIPE_ERROR), MS_ERROR);
	printf("read %d write %d\n", cmd->pipe[0], cmd->pipe[1]);
	return (MS_SUCCESS);
}

int	process_child(t_data *minishell, t_parsing_cmd *cmd, int fd[2])
{
	pid_t	pid;
	int		res;

	pid = fork();
	if (pid == -1)
		return (MS_ERROR);
	if (pid == 0)
	{
		dprintf(2, "in %d out %d\n", fd[0], fd[1]);
		if (dup2_fdinout(fd[0], fd[1]))
			return (MS_ERROR);
		// if (fd[0] == 7)
		// {
		// 	char buff[2000];
		// 	read(0, buff, 2000);
		// 	dprintf(2, "red in -%s-\n", buff);
		// }
		close_pipes(cmd);
		res = execcmd(cmd->cmd, minishell);
		if (res == 5)
			return (MS_ERROR);
		else if (res == 2)
		{
			ft_error(MS_COMMAND_NOT_FOUND);
			ft_error(cmd->cmd[0]);
			ft_error("\n");
		}
		exit(1);
	}
	if (cmd->next)
		return (MS_SUCCESS);
	wait(&pid);
	if (WIFEXITED(pid))
		printf("status for %d: %d\n", pid, WEXITSTATUS(pid));
	if (WIFSIGNALED(pid))
		printf("status for %d: %d\n", pid, WTERMSIG(pid));
	return (MS_SUCCESS);
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
	last = NULL;
	cmd = minishell->parsing_cmd;
	while (cmd)
	{
		fd[0] = cmd->fin;
		fd[1] = cmd->fout;
		if (last)
			fd[0] = last->pipe[0];
		if (cmd->next)
			fd[1] = cmd->pipe[1];
		printf("in %d out %d\n", fd[0], fd[1]);
		if (process_child(minishell, cmd, fd))
			return (ft_error(MS_EXEVE_ERROR), perror(""), MS_ERROR);
		last = cmd;
		cmd = cmd->next;
	}
	// waitpid(-1, NULL, 0);
	// cmd = minishell->parsing_cmd;
	// while (cmd)
	// {
	// 	close_pipes(cmd);
	// 	cmd = cmd->next;
	// }
	return (MS_SUCCESS);
}
