/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 02:01:21 by mgama             #+#    #+#             */
/*   Updated: 2023/11/04 13:03:01 by mgama            ###   ########.fr       */
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
	if (ft_strcmp("cd", cmd->cmd[0]) == 0)
		return (ft_builtin_cd());
	else if (ft_strcmp("echo", cmd->cmd[0]) == 0)
		return (ft_builtin_echo(cmd->cmd));
	else if (ft_strcmp("env", cmd->cmd[0]) == 0)
		return (ft_builtin_env(minishell));
	else if (ft_strcmp("export", cmd->cmd[0]) == 0)
		return (ft_builtin_export(minishell, cmd));
	else if (ft_strcmp("unset", cmd->cmd[0]) == 0)
		return (ft_builtin_unset(minishell, cmd));
	else if (ft_strcmp("pwd", cmd->cmd[0]) == 0)
		return (ft_builtin_pwd(minishell));
	else if (ft_strcmp("exit", cmd->cmd[0]) == 0)
		return (ft_builtin_exit(minishell, cmd));
	return (MS_SUCCESS);
}
