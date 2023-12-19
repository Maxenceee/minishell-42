/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:57:59 by mgama             #+#    #+#             */
/*   Updated: 2023/12/19 11:57:51 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_pwd(t_data *minishell, t_parsing_cmd *cmd)
{
	if (cmd->cmd[1] && cmd->cmd[1][0] == '-' && cmd->cmd[1][1])
		return (ft_cmderror_ex("pwd: `", cmd->cmd[1], MS_IVD_OP), MS_ERROR);
	if (minishell->pwd)
		printf("%s", minishell->pwd);
	printf("\n");
	return (MS_SUCCESS);
}
