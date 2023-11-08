/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:58:24 by mgama             #+#    #+#             */
/*   Updated: 2023/11/08 01:55:43 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*/
int	ft_builtin_exit(t_data *ms, t_parsing_cmd *cmd)
{
	int	i;
	int	code;

	i = -1;
	code = 0;
	while (cmd->cmd[++i])
		;
	if (i > 1 && !ft_strisdigit(cmd->cmd[1]))
	{
		write(2, "exit\n", 6);
		ft_cmderror(MS_ERROR_PREFIX, "exit", ": ");
		ft_putfd(STDERR_FILENO, cmd->cmd[1]);
		ft_putfd(STDERR_FILENO, ": numeric argument required\n");
		exit_with_code(ms, 255, NULL);
	}
	if (i > 2)
	{
		ft_cmderror(MS_ERROR_PREFIX, "exit", ": "MS_TOO_MANY);
		return (MS_ERROR);
	}
	write(2, "exit\n", 6);
	if (i == 2)
		code = ft_atoi(cmd->cmd[1]);
	code = code % 256;
	exit_with_code(ms, code, NULL);
	return (MS_SUCCESS);
}
