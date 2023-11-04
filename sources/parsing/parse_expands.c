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

/**
 * 
 * TODO:
 * A normer...
 * 
 */
char	*ft_parse_expands(t_data *minishell, char *arg)
{
	char	*res;
	char	*tmp;
	int		i;
	int		j;
	char	*token;
	int		quoted;
	int		read_env;

	i = -1;
	read_env = 0;
	quoted = 0;
	res = NULL;
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
		if ((read_env || !quoted) && arg[i] == '$' && arg[i + 1] == '?')
		{
			res = exit_status(res);
			if (!res)
				return (NULL);
			i += 2;
		}
		else if ((read_env || !quoted) && arg[i] == '$')
		{
			j = ++i;
			while (ft_isalnum(arg[i]) && i++)
				;
			if (j == i)
				res = ft_strjoin_char(res, '$');
			else
			{
				token = ft_strtcpy(arg + j, i - j);
				if (!token)
					return (NULL);
				tmp = ft_get_env_variable(minishell, token);
				if (tmp)
					res = ft_strjoin(res, tmp);
				free(token);
				i--;
				continue ;
			}
			if (!res)
				return (NULL);
		}
		if (arg[i] == ' ' && !(quoted || read_env))
		{
			res = ft_strjoin_char(res, arg[i]);
			if (!res)
				return (NULL);
			while (!(quoted || read_env) && arg[i] == ' ')
				i++;
			i--;
			continue ;
		}
		res = ft_strjoin_char(res, arg[i]);
		if (!res)
			return (NULL);
	}
	if (!res)
		return (ft_calloc(1, sizeof(char)));
	return (res);
}
