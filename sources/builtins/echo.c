/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:57:34 by mgama             #+#    #+#             */
/*   Updated: 2023/11/01 00:06:15 by mgama            ###   ########.fr       */
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
				token = ft_calloc(i - j + 1, sizeof(char));
				if (!token)
					return (MS_ERROR);
				ft_strlcpy(token, arg + j, i - j);
				token[i - j] = 0;
				ft_print_env_variable(minishell, token);
				free(token);
				i--;
				continue ;
			}
		}
		printf("%c", arg[i]);
	}
	return (MS_SUCCES);
}

int	ft_builtin_echo(t_data *minishell, char *args, int has_newline)
{
	if (check_quotes(args)) // si il manque une quote, n'affiche rien
		return (MS_SUCCES);
	if (ft_print_echo_arg(minishell, args))
		return (ft_error(MS_ERROR_MSG), MS_ERROR);
	if (has_newline)
		printf("\n");
	return (MS_SUCCES);
}
