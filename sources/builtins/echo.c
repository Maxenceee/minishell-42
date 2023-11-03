/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:57:34 by mgama             #+#    #+#             */
/*   Updated: 2023/11/03 17:49:12 by mgama            ###   ########.fr       */
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

/**
 * 
 * TODO:
 * A normer...
 * 
 */
int	ft_print_echo_arg(t_data *minishell, char *arg)
{
	int		i;
	int		j;
	char	*token;
	int		quoted;
	int		read_env;

	i = -1;
	read_env = 0;
	quoted = 0;
	while (arg[++i])
	{
		if (!read_env && arg[i] == '\'')
		{
			quoted = !quoted;
			continue;
		}
		else if (!quoted && arg[i] == '\"')
		{
			read_env = !read_env;
			continue;
		}
		if ((read_env || !quoted) && arg[i] == '$')
		{
			j = ++i;
			while (ft_isalnum(arg[i]) && i++)
				;
			if (j == i)
				printf("$");
			else
			{
				token = ft_strtcpy(arg + j, i - j);
				if (!token)
					return (MS_ERROR);
				ft_print_env_variable(minishell, token);
				free(token);
				i--;
				continue ;
			}
		}
		if (arg[i] == ' ' && !(quoted || read_env))
		{
			printf("%c", arg[i]);
			while (!(quoted || read_env) && arg[i] == ' ')
				i++;
			i--;
			continue ;
		}
		printf("%c", arg[i]);
	}
	return (MS_SUCCESS);
}

int	ft_builtin_echo(char **args)
{
	int	i;
	int	j;
	int	has_newline;

	i = -1;
	has_newline = 0;
	while (args[++i])
	{
		if (i == 1 && ft_strcmp("-n", args[i]) == 0)
		{
			j = 0;
			while (args[i][++j])
			{
				if (args[i][j] != 'n')
					break ;
			}
			has_newline = 1;
			continue ;
		}
		printf("%s", args[i]);
		if (args[i])
			printf(" ");
	}
	if (has_newline)
		printf("\n");
	return (MS_SUCCESS);
}
