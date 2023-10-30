/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffreze <ffreze@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:53:11 by mgama             #+#    #+#             */
/*   Updated: 2023/10/30 16:57:54 by ffreze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	execcmd(char **command, char *envp[])
// {
// 	char		*cmd;

// 	if (command[0] == NULL)
// 		return (5);
// 	cmd = parse_env(envp, command[0]);
// 	if (!cmd || ft_strcmp(command[0], "") == 0)
// 		return (2);
// 	if (execve(cmd, command, envp) == -1)
// 	{
// 		perror("Could not execute execve");
// 		return (1);
// 	}
// 	return (0);
// }

// int	open_fdinout(int idx, t_data *c)
// {
// 	int	fdin;
// 	int	fdout;

// 	if (idx == 0)
// 	{
// 		fdin = open(c->input, O_RDONLY);
// 		if (fdin == -1)
// 			perror(OPEN_IN_ERROR);
// 		if (dup2_fdinout(fdin, c->pipes[1]) < 0)
// 			return (1);
// 	}
// 	else if (idx == c->process_count - 1)
// 	{
// 		fdout = open(c->output, O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 		if (fdout == -1)
// 			exit_error_with_msg(c, OPEN_OUT_ERROR);
// 		if (dup2_fdinout(c->pipes[2 * idx - 2], fdout) < 0)
// 			return (1);
// 	}
// 	else
// 		if (dup2_fdinout(c->pipes[2 * idx - 2],
// 				c->pipes[2 * idx + 1]) < 0)
// 			return (1);
// 	return (0);
// }

// void	process_child(t_data *commands, int idx)
// {
// 	pid_t	pid;
// 	int		res;

// 	pid = fork();
// 	if (pid == -1)
// 		exit_error_with_msg(commands, FORK_ERROR);
// 	if (pid == 0)
// 	{
// 		if (open_fdinout(idx, commands))
// 			return ;
// 		close_pipes(commands);
// 		res = execcmd(commands->command_list[idx], commands->envp);
// 		if (res == 5)
// 			exit_error_with_msg(commands, PERM_DENIED);
// 		else if (res == 2)
// 			ft_putstr_fd(commands->command_list[idx][0], COMMAND_NOT_FOUND, 2);
// 		exit(1);
// 	}
// }

// void	fork_processes(t_data *commands)
// {
// 	int		i;

// 	commands->pipe_nb = 2 * (commands->process_count - 1);
// 	commands->pipes = malloc(sizeof(int) * commands->pipe_nb);
// 	if (!commands->pipes)
// 		exit_error_with_msg(commands, PIPE_ERROR);
// 	create_pipes(commands);
// 	i = -1;
// 	while (++i < commands->process_count)
// 		process_child(commands, i);
// 	close_pipes(commands);
// 	waitpid(-1, NULL, 0);
// }
