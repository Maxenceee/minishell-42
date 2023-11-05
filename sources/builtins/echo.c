/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:57:34 by mgama             #+#    #+#             */
/*   Updated: 2023/11/04 19:11:22 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *string)
{
	int	quoted;
	int	read_env;
	int	i;

	i = -1;
	quoted = 0;
	read_env = 0;
	while (string[++i])
	{
		if (!read_env && string[i] == '\'')
		{
			quoted = !quoted;
		}
		else if (!quoted && string[i] == '\"')
		{
			read_env = !read_env;
		}
	}
	return (quoted || read_env);
}

int	ft_builtin_echo(t_data *minishell, t_parsing_cmd *cmd)
{
	int	i;
	int	j;
	int	has_newline;

	(void)minishell;
	i = 0;
	has_newline = 1;
	while (cmd->cmd[++i])
	{
		if (i == 1 && ft_strcmp("-n", cmd->cmd[i]) == 0)
		{
			j = 0;
			while (cmd->cmd[i][++j])
			{
				if (cmd->cmd[i][j] != 'n')
					break ;
			}
			has_newline = 0;
			continue ;
		}
		printf("%s", cmd->cmd[i]);
		if (cmd->cmd[i])
			printf(" ");
	}
	if (has_newline)
		printf("\n");
	return (MS_SUCCESS);
}
