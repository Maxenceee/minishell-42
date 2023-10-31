/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_env_element.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:35:46 by mgama             #+#    #+#             */
/*   Updated: 2023/10/31 14:36:39 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_env_element(t_env_element *env_e)
{
	if (env_e->key)
		free(env_e->key);
	if (env_e->value)
		free(env_e->value);
	free(env_e);
}
