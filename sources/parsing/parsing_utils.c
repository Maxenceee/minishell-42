/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:52:15 by mgama             #+#    #+#             */
/*   Updated: 2023/11/15 16:42:09 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_joinf_tab(char **tab, char *str)
{
	char	**tmp;
	int		i;

	i = 0;
	while (tab && tab[i])
		i++;
	tmp = (char **)ft_calloc(i + 2, sizeof(char *));
	if (!tmp)
		return (NULL);
	i = -1;
	while (tab && tab[++i])
	{
		tmp[i] = ft_strdup(tab[i]);
		if (!tmp[i])
			return (free_tab(tab),
				free_tab(tmp), NULL);
	}
	if (!tab)
		i = 0;
	if (tab)
		free_tab(tab);
	tmp[i] = ft_strdup(str);
	if (!tmp[i])
		return (free_tab(tmp), NULL);
	return (tmp);
}

int	join_env_var(t_data *ms, char *token, t_expands_p *p)
{
	char	*val;

	val = ft_get_env_variable(ms, token);
	if (!val)
		val = ft_strdup("");
	else
		val = ft_strdup(val);
	if (!val)
		exit_with_error(ms, MS_ERROR, MS_ALLOC_ERROR_MSG);
	if (val)
	{
		ft_replace(val, '\'', -2);
		ft_replace(val, '\"', -3);
		p->res = ft_strjoin(p->res, val);
		free(val);
		if (!p->res)
			exit_with_error(ms, MS_ERROR, MS_ALLOC_ERROR_MSG);
	}
	return (MS_SUCCESS);
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	get_env_var_token(t_data *ms, char *line, t_expands_p *p, int q)
{
	int		j;
	char	*token;

	j = 0;
	if (line[j] && (ft_isalpha(line[j]) || line[j] == '_'))
		j++;
	while (ft_isalnum(line[j]) || line[j] == '_')
		j++;
	if (j == 0 && ((!ft_isalpha(line[j]) && !is_quote(line[j])) || q))
	{
		p->res = ft_strjoin_char(p->res, '$');
		if (!p->res)
			exit_with_error(ms, MS_ERROR, MS_ALLOC_ERROR_MSG);
		return (MS_SUCCESS);
	}
	p->i += j;
	if (j)
	{
		token = ft_strtcpy(line, j);
		if (!token)
			exit_with_error(ms, MS_ERROR, MS_ALLOC_ERROR_MSG);
		join_env_var(ms, token, p);
		free(token);
	}
	return (MS_SUCCESS);
}
