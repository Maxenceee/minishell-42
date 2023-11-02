/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffreze <ffreze@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 18:40:49 by mgama             #+#    #+#             */
/*   Updated: 2023/11/02 16:10:19 by mgama            ###   ########.fr       */
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
