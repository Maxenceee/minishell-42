/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:58:24 by mgama             #+#    #+#             */
/*   Updated: 2023/11/04 13:07:11 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_exit(t_data *ms, t_parsing_cmd *cmd)
{
	int	i;
	int	code;

	i = -1;
	code = 0;
	while (cmd->cmd[++i])
		;
	if (i > 2)
	{
		ft_putfd(STDERR_FILENO, MS_ERROR_PREFIX"exit: too many arguments\n");
		return (MS_ERROR);
	}
	write(2, "exit\n", 6);
	if (i == 2)
		code = ft_atoi(cmd->cmd[1]);
	exit_with_code(ms, code, NULL);
	return (MS_SUCCESS);
}
