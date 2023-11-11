/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:58:24 by mgama             #+#    #+#             */
/*   Updated: 2023/11/11 17:36:25 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_exit(t_data *ms, t_parsing_cmd *cmd)
{
	int		i;
	int64_t	code;

	i = -1;
	code = 0;
	while (cmd->cmd[++i])
		;
	if (i > 1 && !ft_strisdigit(cmd->cmd[1]))
	{
		ft_putfd(STDOUT_FILENO, "exit\n");
		ft_cmderror_ex("exit: ", cmd->cmd[1], ": numeric argument required\n");
		exit_with_code(ms, 2, NULL);
	}
	if (i > 2)
		return (ft_cmderror("exit", ": "MS_TOO_MANY),
			MS_ERROR);
	ft_putfd(STDOUT_FILENO, "exit\n");
	if (i == 2)
		code = ft_atoll(cmd->cmd[1]);
	if ((uint64_t)code > INT64_MAX)
	{
		code = INT64_MAX;
		ft_cmderror_ex("exit: ", cmd->cmd[1], ": numeric argument required\n");
	}
	code = code % 256;
	exit_with_code(ms, code, NULL);
	return (MS_SUCCESS);
}
