/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 02:00:27 by mgama             #+#    #+#             */
/*   Updated: 2023/11/04 19:02:53 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execcmd(char **command, t_data *ms)
{
	char		*cmd;
	char		**envp;

	envp = ms->envp;
	if (command[0] == NULL)
		return (5);
	if (!access(command[0], F_OK))
		execve(command[0], command, envp);
	cmd = parse_env(ms, command[0]);
	if (!cmd || ft_strcmp(command[0], "") == 0)
		return (2);
	if (execve(cmd, command, envp) == -1)
		return (perror(MS_EXEVE_ERROR), MS_ERROR);
	return (MS_NO_ERROR);
}

int	handle_cmd(t_data *minishell, t_parsing_cmd *cmd)
{
	int	exit_code;

	if (cmd->files)
		if (open_fdinout(cmd))
			exit(1);
	if (cmd->builtin)
	{
		exit_code = cmd->builtin(minishell, cmd);
		exit(exit_code);
	}
	exit_code = execcmd(cmd->cmd, minishell);
	if (exit_code == 5)
		exit(1);
	else if (exit_code == 2)
	{
		ft_putfd(2, MS_COMMAND_NOT_FOUND);
		ft_putfd(2, cmd->cmd[0]);
		ft_putfd(2, "\n");
	}
	exit(exit_code);
}
