/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:52:15 by mgama             #+#    #+#             */
/*   Updated: 2023/11/10 21:37:17 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	get_env_var_token(t_data *ms, char *line, t_expands_p *p)
{
	int		j;
	char	*token;

	j = 0;
	while (ft_isalpha(line[j]) || line[j] == '_')
		j++;
	if (j == 0)
	{
		p->res = ft_strjoin_char(p->res, '$');
		if (!p->res)
			exit_with_error(ms, MS_ERROR, MS_ALLOC_ERROR_MSG);
		return (MS_SUCCESS);
	}
	p->i += j;
	token = ft_strtcpy(line, j);
	if (!token)
		exit_with_error(ms, MS_ERROR, MS_ALLOC_ERROR_MSG);
	join_env_var(ms, token, p);
	free(token);
	return (MS_SUCCESS);
}
