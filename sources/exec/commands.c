/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 02:00:27 by mgama             #+#    #+#             */
/*   Updated: 2023/11/09 02:42:55 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execcmd(char **command, t_data *ms)
{
	char		*cmd;
	char		**envp;

	envp = ms->envp;
	if (is_empty(command[0]))
		return (MS_SUCCESS);
	if (is_dir(command[0]))
		(ft_cmderror(MS_ERROR_PREFIX, command[0], ": "MS_IS_DIR), exit(126));
	cmd = parse_env(ms, command[0]);
	if (!cmd)
		return (MS_ERROR);
	if (execve(cmd, command, envp) == -1)
	{
		ft_cmderror(MS_ERROR_PREFIX, command[0], ": ");
		perror("");
		if (access(cmd, F_OK) != 0)
			exit(127);
		else if (access(cmd, X_OK) != 0)
			exit(126);
	}
	return (MS_ERROR);
}

int	handle_cmd(t_data *minishell, t_parsing_cmd *cmd)
{
	if (cmd->files)
		if (open_fdinout(cmd))
			exit(1);
	if (cmd->builtin)
	{
		exit(cmd->builtin(minishell, cmd));
	}
	if (execcmd(cmd->cmd, minishell))
	{
		ft_cmderror(MS_ERROR_PREFIX, cmd->cmd[0], ": "MS_COMMAND_NOT_FOUND);
		exit(127);
	}
	exit(MS_ERROR);
}
