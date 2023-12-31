/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_env_element.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 15:07:16 by mgama             #+#    #+#             */
/*   Updated: 2023/11/10 17:27:55 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_and_reasign_env_e(t_env_element *env_e,
	t_env_element *new_env_e)
{
	while (env_e)
	{
		if (ft_iscmp(env_e->key, new_env_e->key))
		{
			if (new_env_e->value && env_e->value)
			{
				free(env_e->value);
				env_e->value = NULL;
			}
			if (new_env_e->value)
			{
				env_e->value = ft_strdup(new_env_e->value);
				if (!env_e->value)
					return (MS_ERROR);
			}
			destroy_env_element(new_env_e);
			return (MS_NO_ERROR);
		}
		env_e = env_e->next;
	}
	return (MS_SUCCESS);
}

void	link_new_env(t_data *minishell, t_env_element *env_e)
{
	t_env_element	*tmp;
	t_env_element	*prev;

	prev = NULL;
	tmp = minishell->env;
	while (tmp && ft_strcmp(tmp->key, env_e->key) < 0)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (prev == NULL)
	{
		env_e->next = minishell->env;
		minishell->env = env_e;
	}
	else
	{
		prev->next = env_e;
		env_e->next = tmp;
	}
}

int	ft_push_env_element(t_data *minishell, t_env_element *env_e)
{
	int				res;

	if (!env_e)
		exit_with_error(minishell, MS_ERROR, MS_ALLOC_ERROR_MSG);
	res = ft_check_and_reasign_env_e(minishell->env, env_e);
	if (res == MS_ERROR)
		return (MS_ERROR);
	else if (res == MS_NO_ERROR)
		return (MS_SUCCESS);
	link_new_env(minishell, env_e);
	return (MS_SUCCESS);
}
