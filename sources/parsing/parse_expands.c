/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_expands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:59:25 by mgama             #+#    #+#             */
/*   Updated: 2023/11/01 18:00:24 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_exit_code_token(char *arg, char *res, int i)
{
	while (arg[i])
	{
		if (arg[i] == '\'')
		{
			res = ft_strjoin_char(res, arg[i++]);
			while (arg[i] && arg[i] != '\'')
				res = ft_strjoin_char(res, arg[i++]);
		}
		if (arg[i] == '\"')
		{
			res = ft_strjoin_char(res, arg[i++]);
			while (arg[i] && arg[i] != '\"')
			{
				if (arg[i] == '$' && arg[i + 1] == '?')
				{
					res = exit_status(res);
					i += 2;
				}
				res = ft_strjoin_char(res, arg[i++]);
			}
		}
		if (arg[i] == '$' && arg[i + 1] == '?')
		{
			res = exit_status(res);
			i += 2;
		}
		else
			res = ft_strjoin_char(res, arg[i++]);
	}
	return (res);
}

// int	get_exit_code_token(char *arg)
// {
// 	while (*arg)
// 	{
// 		if (*arg == '\'')
// 		{
// 			arg++;
// 			while (*arg && *arg != '\'')
// 				arg++;
// 		}
// 		if (*arg == '\"')
// 		{
// 			arg++;
// 			while (*arg && *arg != '\"')
// 			{
// 				if (*arg == '$' && *(arg + 1) == '?')
// 					return (*arg);
// 				arg++;
// 			}
// 		}
// 		if (*arg == '$' && *(arg + 1) == '?')
// 			return (*arg);
// 		arg++;
// 	}
// 	return (-1);
// }

char	*parse_exit_code(char *arg)
{
	char	*p;

	p = get_exit_code_token(arg, NULL, 0);
}

char	*ft_parse_expands(t_data *minishell, char *arg)
{
	char	*str;

	str = get_exit_code_token(arg, NULL, 0);
	printf("%s\n", str);
}
