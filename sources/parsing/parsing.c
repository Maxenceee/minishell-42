/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffreze <ffreze@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:40:49 by mgama             #+#    #+#             */
/*   Updated: 2023/10/30 15:48:50 by ffreze           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(char *envp[])
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
	}
	return (NULL);
}

char	*parse_env(char *envp[], char *cmd)
{
	char	*path;
	char	**bins;
	char	*joins[3];
	int		i;

	path = get_path(envp);
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
		if (access(path, F_OK) == 0)
			return (path);
	}
	free(bins);
	return (NULL);
}

int	ft_mainloop(t_data *minishell)
{
	char	*line;

	while (!minishell->exit)
	{
		line = readline(MS_PROMPT_NAME);
		if (ft_push_new_command(minishell, line))
			return (ft_error("Error: could not allocate memory.\n"));
		print_linked_list(minishell->parsing_cmd);
		ft_destroy_parsing_cmd(minishell);
	}
	return (MS_SUCCESS);
}
