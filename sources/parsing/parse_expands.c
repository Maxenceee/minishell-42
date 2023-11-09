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

char	*parse_exit_code(char *arg, char *res)
{
	int		i;
	int		quoted;
	int		read_env;

	i = 0;
	read_env = 0;
	quoted = 0;
	while (arg[i])
	{
		if (!read_env && arg[i] == '\'')
			quoted = !quoted;
		if (!quoted && arg[i] == '\"')
			read_env = !read_env;
		if ((read_env || (!read_env && !quoted))
			&& arg[i] == '$' && arg[i + 1] == '?')
		{
			res = exit_status(res);
			if (!res)
				return (NULL);
			i += 2;
			continue ;
		}
		res = ft_strjoin_char(res, arg[i++]);
		if (!res)
			return (NULL);
	}
	return (res);
}

int	get_env_var_token(t_data *ms, char *line, char **res, int *i)
{
	int		j;
	char	*token;
	char	*val;

	j = 0;
	while (ft_isalpha(line[j]) || line[j] == '_')
		j++;
	if (j == 0)
	{
		*res = ft_strjoin_char(*res, '$');
		if (!*res)
			exit_with_error(ms, MS_ERROR, MS_ALLOC_ERROR_MSG);
		return (MS_SUCCESS);
	}
	*i += j;
	token = ft_strtcpy(line, j);
	if (!token)
		exit_with_error(ms, MS_ERROR, MS_ALLOC_ERROR_MSG);
	val = ft_get_env_variable(ms, token);
	if (!val)
		val = ft_strdup("");
	if (val)
		*res = ft_strjoin(*res, val);
	if (val && !*res)
		exit_with_error(ms, MS_ERROR, MS_ALLOC_ERROR_MSG);
	free(token);
	return (MS_SUCCESS);
}

int	is_redirect_token(char a, char n)
{
	return (a == '>' && n != '>' || a == '<' && n != '<');
}

char	*parse_env_var(t_data *ms, char *arg, char *res, int t)
{
	int		i;
	int		quoted;
	int		read_env;
	char	*token;

	i = 0;
	read_env = 0;
	quoted = 0;
	while (arg[i])
	{
		if (!read_env && arg[i] == '\'')
			quoted = !quoted;
		if (!quoted && arg[i] == '\"')
			read_env = !read_env;
		if ((read_env || (!read_env && !quoted)) && arg[i] == '$' && arg[i + 1])
		{
			i++;
			get_env_var_token(ms, arg + i, &res, &i);
			continue ;
		}
		res = ft_strjoin_char(res, arg[i]);
		if (t && (!read_env && !quoted) && is_redirect_token(arg[i], arg[i + 1]))
			res = ft_strjoin_char(res, ' ');
		i++;
	}
	free(arg);
	return (res);
}

char	*ft_parse_expands(t_data *minishell, char *arg, int t)
{
	char	*str;

	str = parse_exit_code(arg, NULL);
	str = parse_env_var(minishell, str, NULL, t);
	return (str);
}
