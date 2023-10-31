/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 17:07:58 by mgama             #+#    #+#             */
/*   Updated: 2023/11/01 00:34:11 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env(t_data *minishell)
{
	t_env_element	*el;

	el = minishell->env;
	while (el)
	{
		printf("%s=%s\n", el->key, el->value);
		el = el->next;
	}
}

void	ft_print_env_variable(t_data *minishell, char *key)
{
	char	*v;

	v = ft_get_env_variable(minishell, key);
	if (v)
		printf("%s", v);
}
