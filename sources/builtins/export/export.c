/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:58:07 by mgama             #+#    #+#             */
/*   Updated: 2023/11/03 17:35:15 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_export(t_data *minishell, t_parsing_cmd *cmd)
{
	char	**env_e;
	int		i;

	i = 0;
	while (cmd->cmd[++i])
	{
		env_e = ft_split(cmd->cmd[i], "=");
		if (!env_e)
			exit(1);
		ft_push_env_element(minishell, ft_new_env_element(env_e[0], env_e[1]));
	}
	return (MS_SUCCESS);
}
