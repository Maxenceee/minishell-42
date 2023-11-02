/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:05:16 by mgama             #+#    #+#             */
/*   Updated: 2023/11/02 17:12:59 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cmd_count(char *line)
{
	int		j;
	int		i;
	int		quoted;
	int		read_env;

	i = -1;
	j = 0;
	read_env = 0;
	quoted = 0;
	while (line[++i])
	{
		if (!read_env && line[i] == '\'')
			quoted = !quoted;
		else if (!quoted && line[i] == '\"')
			read_env = !read_env;
		while (!(quoted || read_env) && line[i] == ' ')
			i++;
		if (!(quoted || read_env) && line[i])
			j++;
		while (!(quoted || read_env) && line[i] != ' ' && line[i])
			i++;
	}
	return (j);
}

int	get_cmd_len(char *line)
{
	int	i;
	int	quoted;
	int	read_env;

	i = -1;
	read_env = 0;
	quoted = 0;
	while (line[++i] && (line[i] != ' ' || (quoted || read_env)))
	{
		if (!read_env && line[i] == '\'')
			quoted = !quoted;
		else if (!quoted && line[i] == '\"')
			read_env = !read_env;
	}
	return (i);
}

char	*put_cmd(t_data *minishell, char *line, int *i)
{
	char	*res;
	char	*cmd;
	int		len;

	len = get_cmd_len(line);
	res = ft_strtcpy(line, len);
	if (!res)
		return (NULL);
	*i += len;
	cmd = ft_parse_expands(minishell, res);
	free(res);
	return (cmd);
}

char	**ft_split_cmd(t_data *minishell, char *line)
{
	int		i;
	int		j;
	char	**res;
	int		ccount;

	ccount = cmd_count(line);
	res = (char **)ft_calloc(ccount, sizeof(char *));
	if (!res)
		return (NULL);
	i = -1;
	j = -1;
	while (line[++i])
	{
		while (line[i] == ' ')
			i++;
		if (line[i])
			res[++j] = put_cmd(minishell, line + i, &i);
		while (line[i] && line[i] != ' ')
			i++;
	}
	return (res);
}
