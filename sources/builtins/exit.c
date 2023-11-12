/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:58:24 by mgama             #+#    #+#             */
/*   Updated: 2023/11/12 20:51:59 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	safe_atoll(const char *str, int64_t *result)
{
	int			i;
	int64_t		nbr;
	int			sign;

	i = 0;
	nbr = 0;
	sign = 0;
	if ((char)str[i] == '-' || (char)str[i] == '+')
		if ((char)str[i++] == '-')
			sign++;
	while ((char)str[i] >= '0' && (char)str[i] <= '9')
	{
		if ((sign % 2 != 1 && nbr > (INT64_MAX - ((char)str[i] - '0')) / 10)
			|| - nbr < (INT64_MIN + ((char)str[i] - '0')) / 10)
			return (MS_ERROR);
		nbr = nbr * 10 + ((char)str[i++] - '0');
	}
	if (sign % 2 == 1)
		*result = (nbr * -1);
	else
		*result = nbr;
	return (MS_SUCCESS);
}

int64_t	get_exit_code(int i, char *cmd)
{
	int64_t	code;
	int		valid;

	code = 0;
	valid = 1;
	if (i == 2)
		valid = !safe_atoll(cmd, &code);
	if (!valid)
	{
		code = INT64_MAX;
		ft_cmderror_ex("exit: ", cmd, ": numeric argument required\n");
	}
	code = code % 256;
	return (code);
}

#ifdef __APPLE__

int	ft_builtin_exit(t_data *ms, t_parsing_cmd *cmd)
{
	int		i;
	int64_t	code;

	i = -1;
	while (cmd->cmd[++i])
		;
	if (i > 1 && !ft_strisdigit(cmd->cmd[1]))
	{
		ft_putfd(STDOUT_FILENO, "exit\n");
		ft_cmderror_ex("exit: ", cmd->cmd[1], ": numeric argument required\n");
		exit_with_code(ms, 255, NULL);
	}
	if (i > 2)
		return (ft_cmderror("exit", ": "MS_TOO_MANY), MS_ERROR);
	ft_putfd(STDOUT_FILENO, "exit\n");
	code = get_exit_code(i, cmd->cmd[1]);
	exit_with_code(ms, code, NULL);
	return (MS_SUCCESS);
}

#else

int	ft_builtin_exit(t_data *ms, t_parsing_cmd *cmd)
{
	int		i;
	int64_t	code;

	i = -1;
	while (cmd->cmd[++i])
		;
	if (i > 1 && !ft_strisdigit(cmd->cmd[1]))
	{
		ft_putfd(STDOUT_FILENO, "exit\n");
		ft_cmderror_ex("exit: ", cmd->cmd[1], ": numeric argument required\n");
		exit_with_code(ms, 2, NULL);
	}
	if (i > 2)
		return (ft_cmderror("exit", ": "MS_TOO_MANY), MS_ERROR);
	ft_putfd(STDOUT_FILENO, "exit\n");
	code = get_exit_code(i, cmd->cmd[1]);
	exit_with_code(ms, code, NULL);
	return (MS_SUCCESS);
}

#endif /* __APPLE__ */