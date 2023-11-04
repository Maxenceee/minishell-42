/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:58:27 by mgama             #+#    #+#             */
/*   Updated: 2023/11/04 19:11:02 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_env(t_data *minishell, t_parsing_cmd *cmd)
{
	(void)cmd;
	print_env(minishell);
	return (MS_SUCCESS);
}
