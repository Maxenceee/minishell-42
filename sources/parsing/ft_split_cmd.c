/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:05:16 by mgama             #+#    #+#             */
/*   Updated: 2023/11/15 16:08:07 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_spaces_in_quotes(char *arg, char cmp, int *i)
{
	(*i)++;
	while (arg[*i] && arg[*i] != cmp)
	{
		if (arg[*i] == ' ')
			arg[*i] = -1;
		if (arg[*i] == '>')
			arg[*i] = -5;
		if (arg[*i] == '<')
			arg[*i] = -6;
		(*i)++;
	}
}

void	replace_spaces(char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'')
			replace_spaces_in_quotes(arg, '\'', &i);
		if (arg[i] == '\"')
			replace_spaces_in_quotes(arg, '\"', &i);
		i++;
	}
}

void	replace_quotes(char *str)
{
	char	last_opened;

	last_opened = 0;
	while (*str && !last_opened)
	{
		if (*str == '\'' || *str == '"')
		{
			last_opened = *str;
			ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
		}
		else
			str++;
	}
	while (*str && last_opened)
	{
		if (*str && *str == last_opened)
		{
			last_opened = 0;
			ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
		}
		else
			str++;
	}
	if (*str)
		return (replace_quotes(str));
}

char	**ft_split_cmd(char *arg)
{
	int		i;
	char	**cmds;

	replace_spaces(arg);
	cmds = ft_split(arg, " ");
	if (!cmds)
		return (NULL);
	i = -1;
	while (cmds[++i])
	{
		replace_quotes(cmds[i]);
		ft_replace(cmds[i], -1, ' ');
		ft_replace(cmds[i], -2, '\'');
		ft_replace(cmds[i], -3, '\"');
	}
	return (cmds);
}
