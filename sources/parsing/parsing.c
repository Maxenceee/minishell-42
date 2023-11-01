/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:40:49 by mgama             #+#    #+#             */
/*   Updated: 2023/11/01 15:42:52 by mgama            ###   ########.fr       */
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
	int		i;
	char	*line;
	char	**pipline;
	
	while (!minishell->exit)
	{
		i = -1;
		line = readline(MS_PROMPT_NAME);
		ft_builtin_echo(minishell, line, 1);
		// pipline = ft_split(line, "|");
		// if(!pipline)
		// 	return (ft_error(MS_ALLOC_ERROR_MSG), MS_ERROR);
		// while (pipline[++i])
		// {
		// 	if (ft_push_new_command(minishell, pipline[i]))
		// 		return (ft_error(MS_ALLOC_ERROR_MSG), MS_ERROR);
		// 	print_linked_list(minishell->parsing_cmd);
		// }
		// free_tab(pipline);
		// ft_destroy_parsing_cmd(minishell);
		free(line);
	}
	return (MS_SUCCESS);
}
