/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:57:59 by mgama             #+#    #+#             */
/*   Updated: 2023/11/01 15:35:06 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_pwd(t_data *minishell)
{
	// ft_print_env_variable(minishell, "PWD");
	printf("\n");
	return (MS_SUCCESS);
}
