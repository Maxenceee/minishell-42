/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:53:11 by mgama             #+#    #+#             */
/*   Updated: 2023/11/04 00:58:50 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_parsing_cmd *cmd)
{
	return (ft_strcmp("cd", cmd->cmd[0]) == 0
	|| ft_strcmp("echo", cmd->cmd[0]) == 0
	|| ft_strcmp("env", cmd->cmd[0]) == 0
	|| ft_strcmp("export", cmd->cmd[0]) == 0
	|| ft_strcmp("unset", cmd->cmd[0]) == 0
	|| ft_strcmp("pwd", cmd->cmd[0]) == 0
	|| ft_strcmp("exit", cmd->cmd[0]) == 0);
}

int	exec_builtin(t_data *minishell, t_parsing_cmd *cmd)
{
	dprintf(2, "run built in: %s\n", cmd->cmd[0]);
	if (ft_strcmp("cd", cmd->cmd[0]) == 0)
		ft_builtin_cd();
	else if (ft_strcmp("echo", cmd->cmd[0]) == 0)
		ft_builtin_echo(cmd->cmd);
	else if (ft_strcmp("env", cmd->cmd[0]) == 0)
		ft_builtin_env(minishell);
	else if (ft_strcmp("export", cmd->cmd[0]) == 0)
		ft_builtin_export(minishell, cmd);
	else if (ft_strcmp("unset", cmd->cmd[0]) == 0)
		ft_builtin_unset(minishell, cmd);
	else if (ft_strcmp("pwd", cmd->cmd[0]) == 0)
		ft_builtin_pwd(minishell);
	else if (ft_strcmp("exit", cmd->cmd[0]) == 0)
		ft_builtin_exit();
	return (MS_SUCCESS);
}

int	execcmd(char **command, t_data *ms)
{
	char		*cmd;
	char		**envp;

	envp = ms->envp;
	if (command[0] == NULL)
		return (5);
	cmd = parse_env(ms, command[0]);
	if (!cmd || ft_strcmp(command[0], "") == 0)
		return (2);
	printf("execve(%s)\n", cmd);
	if (execve(cmd, command, envp) == -1)
		return (perror(MS_EXEVE_ERROR), MS_ERROR);
	return (MS_NO_ERROR);
}

int	check_fd_heredoc(t_parsing_cmd *cmd, int pip[2])
{
	if (cmd->here_doc_fname)
	{
		close(pip[0]);
		return (open(cmd->here_doc_fname, O_RDONLY));
	}
	return (pip[0]);
}

int	handle_infile(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (ft_error(MS_ERROR_PREFIX),
			perror(""), ft_error("\n"), MS_ERROR);
	if (fd > 0 && dup2(fd, STDIN_FILENO) < 0)
		return (ft_error(MS_PIPE_ERROR), MS_ERROR);
	if (fd > 0)
		close(fd);
	return (MS_SUCCESS);
}

int	handle_outfile(t_parsing_file *f, char *file_name)
{
	int	fd;

	if (f->type == REDIR_OUT)
		fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	else
		fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
		return (ft_error(MS_ERROR_PREFIX),
			perror(""), ft_error("\n"), MS_ERROR);
	if (fd > 0 && dup2(fd, STDIN_FILENO) < 0)
		return (ft_error(MS_PIPE_ERROR), MS_ERROR);
	if (fd > 0)
		close(fd);
	return (MS_SUCCESS);
}

int	open_fdinout(t_parsing_cmd *cmd)
{
	t_parsing_file	*f;

	f = cmd->files;
	while (f)
	{
		if (f->type == REDIR_IN)
		{
			if (handle_infile(f->file_name))
				return (MS_ERROR);
		}
		else if (f->type == REDIR_OUT || f->type == CONCAT_OUT)
		{
			if (handle_outfile(f, f->file_name))
				return (MS_ERROR);
		}
		else if (f->type == CONCAT_IN)
		{
			if (handle_infile(f->file_name))
				return (MS_ERROR);
		}
		f = f->next;
	}
	return (MS_SUCCESS);
}

int	dup_cmd(t_data *minishell, t_parsing_cmd *cmd, int pip[2])
{
	int	exit_code;

	dprintf(2, "pipe read %d write %d\n", cmd->fin, pip[1]);
	dprintf(2, "cmd files %p\n", cmd->files);
	if (cmd->prev && dup2(cmd->fin, STDIN_FILENO) < 0)
		return (MS_ERROR);
	close(pip[0]);
	if (cmd->next && dup2(pip[1], STDOUT_FILENO) < 0)
		return (MS_ERROR);
	close(pip[1]);
	if (cmd->prev)
		close(cmd->fin);
	if (cmd->files)
		if (open_fdinout(cmd))
			exit(1);
	if (is_builtin(cmd))
		if (exec_builtin(minishell, cmd))
			exit(1);
	exit_code = execcmd(cmd->cmd, minishell);
	if (exit_code == 5)
		exit(1);
	else if (exit_code == 2)
	{
		ft_error(MS_COMMAND_NOT_FOUND);
		ft_error(cmd->cmd[0]);
		ft_error("\n");
	}
	exit(exit_code);
}

int	process_child(t_data *minishell, t_parsing_cmd *cmd, int pip[2])
{
	int		res;

	cmd->pid = fork();
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

int	process_wait(t_data *ms)
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
		return (WEXITSTATUS(status));
	return (MS_SUCCESS);
}

int	fork_processes(t_data *minishell)
{
	int				fin;
	int				pip[2];
	t_parsing_cmd	*cmd;

	// signal(SIGQUIT, sigquit_handler);
	g_signal.in_cmd = 1;
	fin = STDIN_FILENO;
	cmd = minishell->parsing_cmd;
	while (cmd)
	{
		cmd->fin = fin;
		if (cmd->next)
			if (pipe(pip) == -1)
				return (MS_ERROR);
		open_heredoc(minishell, cmd);
		if (process_child(minishell, cmd, pip))
			return (MS_ERROR);
		close(pip[1]);
		if (cmd->prev)
			close(cmd->fin);
		fin = check_fd_heredoc(cmd, pip);
		cmd = cmd->next;
	}
	process_wait(minishell);
	g_signal.in_cmd = 0;
	return (MS_SUCCESS);
}

int	mini_exec(t_data *minishell)
{
	if (fork_processes(minishell))
		return (MS_ERROR);
	return (MS_SUCCESS);
}
