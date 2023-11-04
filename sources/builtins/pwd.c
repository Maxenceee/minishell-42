/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:57:59 by mgama             #+#    #+#             */
/*   Updated: 2023/11/04 19:14:12 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_pwd(t_data *minishell, t_parsing_cmd *cmd)
{
	(void)cmd;
	if (minishell->pwd)
		printf("%s", minishell->pwd);
	printf("\n");
	return (MS_SUCCESS);
}
