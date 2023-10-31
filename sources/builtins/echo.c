/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:57:34 by mgama             #+#    #+#             */
/*   Updated: 2023/10/31 17:17:39 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tokens(char *string)
{
	int	i;
	int	d;

	i = -1;
	d = 0;
	while (string[++i])
	{
		printf("%d - %c\n", i, string[i]);
		// if (string[i] == '\'')
		// {
		// 	d++;
		// 	while (string[++i] != '\'')
		// 		;
		// 	if (!string[i])
		// 		return (-1);
		// }
		if (string[i] == '\"' && i++)
		{
			d++;
			while (string[i] != '\"')
				i++;
			if (!string[i])
				return (-1);
		}

		while (string[i] && string[i] == ' ')
			i++;
		if (string[i])
			d++;
		while (string[i] && string[i] != ' ')
			i++;
		// printf("d %d i %d\n", d, i);
	}
	return (d);
}

t_echo_token	*tokenize_string(char *string)
{
	printf("token count: %d\n", count_tokens(string));
	return (NULL);
}

/**
 * 
 * Reproduit le comportement de echo "" (interprete les var d'env)
 * 
 */
int	ft_print_echo_arg(t_data *minishell, char *arg, int read_env)
{
	int		i;
	int		j;
	char	c;
	char	*token;

	i = -1;
	while (arg[++i])
	{
		if (read_env && arg[i] == '$')
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
			}
		}
		printf("%c", arg[i]);
	}
	return (MS_SUCCES);
}

/**
 * 
 * A modifier plus tard, pour pouvoir gerer les espaces entres les differentes chaines
 * ex : echo "aa" "aa" => "aa aa"
 * ex : echo "aa""aa" => "aaaa"
 * 
 */
int	ft_builtin_echo(t_data *minishell, char *args, int has_newline)
{
	int		i;
	char	**splt;

	tokenize_string(args);
	// splt = ft_split(args, " ");
	// if (!splt)
	// 	return (ft_error(MS_ERROR_MSG), MS_ERROR);
	// i = -1;
	// while (splt[++i])
	// {
		// if (ft_print_echo_arg(minishell, splt[i]))
		// 		return (ft_error(MS_ERROR_MSG), MS_ERROR);
	// 	if (splt[i + 1])
	// 		printf(" ");
	// }
	if (has_newline)
		printf("\n");
	return (MS_SUCCES);
}
