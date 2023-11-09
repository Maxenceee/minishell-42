/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:40:49 by mgama             #+#    #+#             */
/*   Updated: 2023/11/09 02:37:15 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_empty(char *str)
{
	if (!str)
		return (1);
	while (*str)
	{
		if (*str != ' ')
			return (0);
		str++;
	}
	return (1);
}

int	is_dir(char *str)
{
	struct stat	f;

	if (lstat(str, &f) != 0)
		return (0);
	if (S_ISDIR(f.st_mode))
	{
		if (*str == '.')
			str++;
		if (*str == '.')
			str++;
		if (*str == '/')
			return (1);
	}
	return (0);
}

int	is_local_path(char *command)
{
	if (*command == '.')
		command++;
	if (*command == '.')
		command++;
	if (*command == '/')
		return (1);
	return (0);
}

char	*local_path(t_data *ms, char *command)
{
	char	*joins[3];
	char	*path;

	if (*command == '/')
		return (ft_strdup(command));
	joins[0] = ft_get_env_variable(ms, "PWD");
	joins[1] = "/";
	joins[2] = command;
	return (ft_strjoin_arr(3, joins, ""));
}

char	*parse_env(t_data *ms, char *cmd)
{
	char	*path;
	char	**bins;
	char	*joins[3];
	int		i;

	if (is_local_path(cmd))
		return (local_path(ms, cmd));
	path = ft_get_env_variable(ms, "PATH");
	if (!path)
		return (NULL);
	bins = ft_split(path, ":");
	if (!bins)
		return (NULL);
	i = -1;
	while (bins[++i])
	{
		joins[0] = bins[i];
		joins[1] = "/";
		joins[2] = cmd;
		path = ft_strjoin_arr(3, joins, "");
		if (!path)
			return (free_tab(bins), NULL);
		if (access(path, F_OK) == 0)
			return (path);
	}
	free_tab(bins);
	return (NULL);
}
