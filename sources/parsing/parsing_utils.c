/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:52:15 by mgama             #+#    #+#             */
/*   Updated: 2023/11/09 13:52:37 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	join_env_var(t_data *ms, char *token, t_expands_p *p)
{
	char	*val;

	val = ft_get_env_variable(ms, token);
	if (!val)
		val = ft_strdup("");
	if (!val)
		exit_with_error(ms, MS_ERROR, MS_ALLOC_ERROR_MSG);
	if (val)
		p->res = ft_strjoin(p->res, val);
	if (val && !p->res)
		exit_with_error(ms, MS_ERROR, MS_ALLOC_ERROR_MSG);
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
