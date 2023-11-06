/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 02:00:27 by mgama             #+#    #+#             */
/*   Updated: 2023/11/06 00:19:06 by mgama            ###   ########.fr       */
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
	if (!cmd)
		return (MS_ERROR);
	if (execve(cmd, command, envp) == -1)
		return (perror(MS_EXEVE_ERROR), MS_ERROR);
	return (MS_ERROR);
}

void	check_perms(t_data *minishell, t_parsing_cmd *pcmd, char *cmd)
{
	struct stat	f;
	int			flag;

	if (lstat(cmd, &f) != -1)
	{
		flag = f.st_mode & S_IFMT;
		if (flag == S_IFDIR && (cmd[ft_strlen(cmd) - 1] == '/'
			|| ft_strncmp(cmd, "./", 2) == 0))
			return (ft_cmderror(MS_ERROR_PREFIX, cmd, ": "MS_IS_DIR), exit(126));
		else if ((ft_strncmp(cmd, "./", 2) == 0 || ft_strncmp(cmd, "/", 1) == 0)
			&& (f.st_mode & S_IXUSR) && (f.st_mode & S_IRUSR))
			return ;
		else if (flag != S_IXUSR && flag != S_IRUSR
			&& flag != S_IFDIR && flag != S_IFLNK)
			return (ft_cmderror(MS_ERROR_PREFIX, cmd, ": "MS_PERM_DENIED), exit(126));
	}
	else if (ft_strncmp(cmd, "./", 2) == 0
		|| ft_strncmp(cmd, "/", 1) == 0)
		return (ft_cmderror(MS_ERROR_PREFIX, cmd, ": "MS_NO_FILE_DIR), exit(127));
	return (ft_cmderror(MS_ERROR_PREFIX, cmd, ": "MS_COMMAND_NOT_FOUND), exit(127));
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
		check_perms(minishell, cmd, cmd->cmd[0]);
	}
	exit(MS_ERROR);
}
