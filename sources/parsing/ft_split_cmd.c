/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:05:16 by mgama             #+#    #+#             */
/*   Updated: 2023/11/08 23:24:49 by mgama            ###   ########.fr       */
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

// void	replace_quotes(char **arg)
// {
// 	int		i;
// 	int		quoted;
// 	int		read_env;
// 	char	*r;

// 	i = 0;
// 	read_env = 0;
// 	quoted = 0;
// 	r = NULL;
// 	while ((*arg)[i])
// 	{
// 		if (!read_env && (*arg)[i] == '\'')
// 		{
// 			i++;
// 			while ((*arg)[i] && (*arg)[i] != '\'')
// 				r = ft_strjoin_char(r, (*arg)[i++]);
// 			quoted = !quoted;
// 			continue ;
// 		}
// 		if (!quoted && (*arg)[i] == '\"')
// 		{
// 			i++;
// 			while ((*arg)[i] && (*arg)[i] != '\"')
// 				r = ft_strjoin_char(r, (*arg)[i++]);
// 			read_env = !read_env;
// 			continue ;
// 		}
// 		r = ft_strjoin_char(r, (*arg)[i++]);
// 	}
// 	free(*arg);
// 	if (!r)
// 		r = ft_calloc(1, sizeof(char));
// 	*arg = r;
// }

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
	i = -1;
	while (cmds[++i])
	{
		replace_quotes(cmds[i]);
		ft_replace(cmds[i], -1, ' ');
	}
	return (cmds);
}
