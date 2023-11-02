/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:40:31 by mgama             #+#    #+#             */
/*   Updated: 2023/11/02 15:53:45 by mgama            ###   ########.fr       */
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
	printf("\n\n\n\nenv count %d\n", i);
	return (i);
}

char	**dup_env(t_data *ms)
{
	int				i;
	char			**res;
	t_env_element	*e;

	i = 0;
	res = ft_calloc(get_env_count(ms), sizeof(char));
	if (!res)
		return (NULL);
	e = ms->env;
	while (e)
	{
		// printf("%s=%s - key len %zu\n", e->key, e->value, ft_strlen(e->key));
		res[i] = ft_strdup(e->key);
		// if (e->value)
		// {
		// 	res[i] = ft_strjoin(res[i], "=");
		// 	res[i] = ft_strjoin(res[i], e->value);
		// }
		printf("res[%d]: %s\n", i, e->key);
		printf("res[%d]: %d\n", i, res[i] == NULL);
		e = e->next;
		i++;
	}
	return (res);
}
