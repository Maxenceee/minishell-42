/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:56:42 by mgama             #+#    #+#             */
/*   Updated: 2023/10/31 14:58:34 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_data *minishell)
{
	t_env_element	*tmp;
	t_env_element	*next;

	tmp = minishell->env;
	while (tmp)
	{
		next = tmp->next;
		destroy_env_element(tmp);
		tmp = next;
	}
}
