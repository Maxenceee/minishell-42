/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 02:01:21 by mgama             #+#    #+#             */
/*   Updated: 2023/11/09 13:21:05 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_no_out(t_parsing_cmd *cmd)
{
	return (ft_iscmp("cd", cmd->cmd[0])
		|| ft_iscmp("export", cmd->cmd[0])
		|| ft_iscmp("unset", cmd->cmd[0])
		|| ft_iscmp("exit", cmd->cmd[0]));
}

void	*get_builtin(char *cmd)
{
	if (ft_iscmp("cd", cmd))
		return (&ft_builtin_cd);
	else if (ft_iscmp("echo", cmd))
		return (&ft_builtin_echo);
	else if (ft_iscmp("env", cmd))
		return (&ft_builtin_env);
	else if (ft_iscmp("export", cmd))
		return (&ft_builtin_export);
	else if (ft_iscmp("unset", cmd))
		return (&ft_builtin_unset);
	else if (ft_iscmp("pwd", cmd))
		return (&ft_builtin_pwd);
	else if (ft_iscmp("exit", cmd))
		return (&ft_builtin_exit);
	return (NULL);
}
