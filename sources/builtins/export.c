/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:58:07 by mgama             #+#    #+#             */
/*   Updated: 2023/10/31 13:23:10 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_export(t_data *minishell)
{
	ft_push_env_element(minishell, "TMP=oui");
	return (MS_SUCCES);
}
