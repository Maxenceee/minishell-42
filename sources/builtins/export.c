/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:58:07 by mgama             #+#    #+#             */
/*   Updated: 2023/11/01 15:35:06 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_export(t_data *minishell, char *key, char *value)
{
	ft_push_env_element(minishell, ft_new_env_element(key, value));
	return (MS_SUCCESS);
}
