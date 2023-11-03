/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:40:31 by mgama             #+#    #+#             */
/*   Updated: 2023/11/03 19:45:01 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env_count(t_data *ms)
{
	int				i;
	t_env_element	*e;

	i = 0;
	e = ms->env;
	while (e)
	{
		i++;
		e = e->next;
	}
	return (i);
}

char	**dup_env(t_data *ms)
{
	int				i;
	char			**res;
	char			*row;
	t_env_element	*e;

	i = 0;
	res = (char **)ft_calloc(get_env_count(ms), sizeof(char *));
	if (!res)
		return (NULL);
	e = ms->env;
	while (e)
	{
		row = ft_strdup(e->key);
		if (e->value)
		{
			row = ft_strjoin(row, "=");
			row = ft_strjoin(row, e->value);
		}
		res[i++] = row;
		e = e->next;
	}
	return (res);
}
