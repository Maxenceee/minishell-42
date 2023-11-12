/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:57:34 by mgama             #+#    #+#             */
/*   Updated: 2023/11/12 16:23:34 by mgama            ###   ########.fr       */
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

int	handle_new_line(t_parsing_cmd *cmd, int i, int *has_newline)
{
	int	j;

	j = 0;
	while (cmd->cmd[i][++j])
	{
		if (cmd->cmd[i][j] != 'n')
		{
			if (cmd->cmd[i][j])
				return (1);
		}
	}
	*has_newline = 0;
	return (0);
}

int	ft_builtin_echo(t_data *minishell, t_parsing_cmd *cmd)
{
	int	i;
	int	has_newline;
	int	t;

	(void)minishell;
	i = 0;
	t = 0;
	has_newline = 1;
	while (cmd->cmd[++i])
	{
		if (!t && ft_strncmp("-n", cmd->cmd[i], 2) == 0)
		{
			if (!handle_new_line(cmd, i, &has_newline))
				continue ;
		}
		else
			t = 1;
		printf("%s", cmd->cmd[i]);
		if (cmd->cmd[i + 1])
			printf(" ");
	}
	if (has_newline)
		printf("\n");
	return (MS_SUCCESS);
}
