/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 02:01:21 by mgama             #+#    #+#             */
/*   Updated: 2023/11/04 19:05:14 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_no_out(t_parsing_cmd *cmd)
{
	return (ft_strcmp("cd", cmd->cmd[0]) == 0
	|| ft_strcmp("export", cmd->cmd[0]) == 0
	|| ft_strcmp("unset", cmd->cmd[0]) == 0
	|| ft_strcmp("exit", cmd->cmd[0]) == 0);
}

void	*get_builtin(char *cmd)
{
	if (ft_strcmp("cd", cmd) == 0)
		return (&ft_builtin_cd);
	else if (ft_strcmp("echo", cmd) == 0)
		return (&ft_builtin_echo);
	else if (ft_strcmp("env", cmd) == 0)
		return (&ft_builtin_env);
	else if (ft_strcmp("export", cmd) == 0)
		return (&ft_builtin_export);
	else if (ft_strcmp("unset", cmd) == 0)
		return (&ft_builtin_unset);
	else if (ft_strcmp("pwd", cmd) == 0)
		return (&ft_builtin_pwd);
	else if (ft_strcmp("exit", cmd) == 0)
		return (&ft_builtin_exit);
	return (NULL);
}
