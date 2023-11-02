/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:40:49 by mgama             #+#    #+#             */
/*   Updated: 2023/11/02 02:38:15 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*parse_env(t_data *ms, char *cmd)
{
	char	*path;
	char	**bins;
	char	*joins[3];
	int		i;

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
		if (access(path, F_OK | X_OK) == 0)
			return (path);
	}
	free_tab(bins);
	return (NULL);
}

int	ft_mainloop(t_data *minishell)
{
	int		i;
	char	*line;
	char	*cmd;
	char	**pipline;
	
	while (!minishell->exit)
	{
		i = -1;
		line = readline(MS_PROMPT_NAME);
		add_history(line);
		pipline = ft_split(line, "|");
		if(!pipline)
			return (ft_error(MS_ALLOC_ERROR_MSG), MS_ERROR);
		while (pipline[++i])
		{
			if (ft_push_new_command(minishell, pipline[i]))
				return (ft_error(MS_ALLOC_ERROR_MSG), MS_ERROR);
			// print_linked_list(minishell->parsing_cmd);
		}
		if (fork_processes(minishell))
			return (MS_ERROR);
		ft_destroy_parsing_cmd(minishell);
		free_tab(pipline);
		free(line);
	}
	return (MS_SUCCESS);
}
