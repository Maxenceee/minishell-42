/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:58:12 by mgama             #+#    #+#             */
/*   Updated: 2023/11/15 17:01:14 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_unset_key(char *key)
{
	int	i;

	i = 0;
	if (key[i] && (ft_isalpha(key[i]) || key[i] == '_'))
		i++;
	else
		return (MS_ERROR);
	while (key[i] && (ft_isalnum(key[i]) || key[i] == '_'))
		i++;
	if (key[i] != '\0' || i == 0)
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
		if (ft_iscmp(env_e->key, key))
		{
			if (!last)
				minishell->env = env_e->next;
			else
				last->next = env_e->next;
			destroy_env_element(env_e);
			break ;
		}
		last = env_e;
		env_e = env_e->next;
	}
}

int	ft_builtin_unset(t_data *minishell, t_parsing_cmd *cmd)
{
	int	i;
	int	code;

	i = 0;
	code = MS_SUCCESS;
	if (cmd->cmd[1] && cmd->cmd[1][0] == '-')
		return (ft_cmderror_ex("unset: `", cmd->cmd[1], MS_IVD_OP), 2);
	while (cmd->cmd[++i])
	{
		if (check_unset_key(cmd->cmd[i]))
		{
			ft_cmderror_ex("unset: `", cmd->cmd[i], MS_IVD_ID);
			code = MS_ERROR;
			continue ;
		}
		unset_env(minishell, cmd->cmd[i]);
	}
	return (code);
}
