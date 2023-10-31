/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_env_element.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:26:16 by mgama             #+#    #+#             */
/*   Updated: 2023/10/30 17:06:18 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_push_env_element(t_data *minishell, char *line)
{
	char			**splt;
	t_env_element	*env_e;
	t_env_element	*tmp;
	
	env_e =	ft_calloc(1, sizeof(t_env_element));
	if (!env_e)
		return (MS_ERROR);
	splt = ft_split(line, "=");
	if (!splt)
		return (free(env_e), MS_ERROR);
	env_e->key = ft_strdup(splt[0]);
	if (!env_e->key)
		return (free(env_e), free_tab(splt), MS_ERROR);
	if (splt[1])
	{
		env_e->value = ft_strdup(splt[1]);
		if (!env_e->value)
			return (free(env_e), free_tab(splt), free(env_e->key), MS_ERROR);
	}
	free_tab(splt);
	tmp = minishell->env;
	while (tmp)
	{
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (!minishell->env)
		minishell->env = env_e;
	else
		tmp->next = env_e;
	return (MS_SUCCES);
}
