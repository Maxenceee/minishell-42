/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:58:12 by mgama             #+#    #+#             */
/*   Updated: 2023/11/03 17:32:33 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_env(t_data *minishell, char *key)
{
	t_env_element	*last;
	t_env_element	*env_e;

	last = NULL;
	env_e = minishell->env;
	while (env_e)
	{
		if (ft_strcmp(env_e->key, key) == 0)
		{
			if (!last)
			{
				minishell->env = env_e->next;
				destroy_env_element(env_e);
			}
			else
			{
				last->next = env_e->next;
				destroy_env_element(env_e);
			}
		}
		last = env_e;
		env_e = env_e->next;
	}
}

int	ft_builtin_unset(t_data *minishell, t_parsing_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[++i])
		unset_env(minishell, cmd->cmd[i]);
	return (MS_SUCCESS);
}
