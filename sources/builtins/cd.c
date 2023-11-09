/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:57:40 by mgama             #+#    #+#             */
/*   Updated: 2023/11/09 13:15:45 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	update_wd(t_data *ms)
{
	ft_push_env_element(ms, ft_new_env_element("OLDPWD", ms->pwd));
	if (ms->pwd)
		free(ms->pwd);
	ms->pwd = getcwd(NULL, sizeof(NULL));
	if (!ms->pwd)
		return (MS_ERROR);
	ft_push_env_element(ms, ft_new_env_element("PWD", ms->pwd));
	return (MS_SUCCESS);
}

int	change_dir(t_data *ms, char *path, char *env_v)
{
	int	res;

	if (env_v && !path)
	{
		ft_cmderror_ex("cd: ", env_v, " not set\n");
		return (MS_ERROR);
	}
	res = chdir(path);
	if (res)
	{
		ft_cmderror("cd: ", "");
		perror(path);
		return (MS_ERROR);
	}
	return (MS_SUCCESS);
}

int	ft_builtin_cd(t_data *minishell, t_parsing_cmd *cmd)
{
	int	status;

	if (!cmd->cmd[1])
		status = change_dir(minishell,
				ft_get_env_variable(minishell, "HOME"), "HOME");
	else if (cmd->cmd[1] && ft_iscmp(cmd->cmd[1], "-"))
	{
		ft_print_env_variable(minishell, "OLDPWD", 1);
		status = change_dir(minishell,
				ft_get_env_variable(minishell, "OLDPWD"), "OLDPWD");
	}
	else
		status = change_dir(minishell, cmd->cmd[1], NULL);
	if (status)
		return (status);
	if (update_wd(minishell))
		return (MS_ERROR);
	return (MS_SUCCESS);
}
