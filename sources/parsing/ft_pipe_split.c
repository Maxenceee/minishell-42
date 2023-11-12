/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 22:01:09 by mgama             #+#    #+#             */
/*   Updated: 2023/11/12 19:48:51 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_pipes_in_quotes(char *arg, char cmp, int *i)
{
	(*i)++;
	while (arg[*i] && arg[*i] != cmp)
	{
		if (arg[*i] == '|')
			arg[*i] = -1;
		(*i)++;
	}
}

void	replace_pipes(char *arg)
{
	int		i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'')
			replace_pipes_in_quotes(arg, '\'', &i);
		if (arg[i] == '\"')
			replace_pipes_in_quotes(arg, '\"', &i);
		i++;
	}
}

char	**ft_pipe_split(char *arg, int *c)
{
	int		i;
	char	**cmds;

	if (!arg)
		return (NULL);
	replace_pipes(arg);
	if (c)
		*c = ft_contains(arg, '|');
	cmds = ft_split(arg, "|");
	i = -1;
	while (cmds[++i])
	{
		ft_replace(cmds[i], -1, '|');
	}
	free(arg);
	return (cmds);
}
