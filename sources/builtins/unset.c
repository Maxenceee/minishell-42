/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:58:12 by mgama             #+#    #+#             */
/*   Updated: 2023/11/04 13:17:32 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unset_key(char *key)
{
	int	i;

	i = -1;
	while (key[++i] && (ft_isalnum(key[i]) || key[i] == '_'))
		;
	if (key[i] != '\0'|| i == 0)
		return (MS_ERROR);
	return (MS_SUCCESS);
}

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
	{
		if (check_unset_key(cmd->cmd[i]))
		{
			ft_putfd(2, MS_ERROR_PREFIX"unset: `");
			ft_putfd(2, cmd->cmd[i]);
			ft_putfd(2, "': not a valid identifier\n");
			continue ;
		}
		unset_env(minishell, cmd->cmd[i]);
	}
	return (MS_SUCCESS);
}
