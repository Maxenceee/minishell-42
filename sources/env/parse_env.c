/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:17:19 by mgama             #+#    #+#             */
/*   Updated: 2023/10/30 17:10:17 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parse_env(t_data *minishell, char **envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (ft_push_env_element(minishell, envp[i]))
			return (MS_ERROR);
	}
	return (MS_SUCCES);
}
