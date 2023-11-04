/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:57:34 by mgama             #+#    #+#             */
/*   Updated: 2023/11/04 02:47:46 by mgama            ###   ########.fr       */
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

int	ft_builtin_echo(char **args)
{
	int	i;
	int	j;
	int	has_newline;

	i = 0;
	has_newline = 1;
	while (args[++i])
	{
		// if (i == 1 && ft_strcmp("-n", args[i]) == 0)
		// {
		// 	j = 0;
		// 	while (args[i][++j])
		// 	{
		// 		if (args[i][j] != 'n')
		// 			break ;
		// 	}
		// 	has_newline = 0;
		// 	continue ;
		// }
		printf("%s", args[i]);
		if (args[i])
			printf(" ");
	}
	if (has_newline)
		printf("\n");
	return (MS_SUCCESS);
}
