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

char	*parse_exit_code(char *arg, t_expands_p *p)
{
	while (arg[p->i])
	{
		if (!p->read_env && arg[p->i] == '\'')
			p->quoted = !p->quoted;
		if (!p->quoted && arg[p->i] == '\"')
			p->read_env = !p->read_env;
		if ((p->read_env || (!p->read_env && !p->quoted))
			&& arg[p->i] == '$' && arg[p->i + 1] == '?')
		{
			p->res = exit_status(p->res);
			if (!p->res)
				return (NULL);
			p->i += 2;
			continue ;
		}
		p->res = ft_strjoin_char(p->res, arg[p->i++]);
		if (!p->res)
			return (NULL);
	}
	return (p->res);
}

int	is_redirect_token(char a, char n)
{
	return ((a == '>' && n != '>') || (a == '<' && n != '<'));
}

char	*parse_env_var(t_data *ms, char *arg, t_expands_p *p, int t)
{
	while (arg[p->i])
	{
		if (!p->read_env && arg[p->i] == '\'')
			p->quoted = !p->quoted;
		if (!p->quoted && arg[p->i] == '\"')
			p->read_env = !p->read_env;
		if ((p->read_env || (!p->read_env && !p->quoted))
			&& arg[p->i] == '$' && arg[p->i + 1])
		{
			p->i++;
			get_env_var_token(ms, arg + p->i, p, p->read_env || p->quoted);
			continue ;
		}
		p->res = ft_strjoin_char(p->res, arg[p->i]);
		if (t && (!p->read_env && !p->quoted)
			&& is_redirect_token(arg[p->i], arg[p->i + 1]))
			p->res = ft_strjoin_char(p->res, ' ');
		p->i++;
	}
	free(arg);
	return (p->res);
}

char	*ft_parse_expands(t_data *minishell, char *arg, int t)
{
	t_expands_p	p;
	char		*str;

	if (t && !ft_strlen(arg))
		return (arg);
	ft_bzero(&p, sizeof(p));
	str = parse_exit_code(arg, &p);
	ft_bzero(&p, sizeof(p));
	str = parse_env_var(minishell, str, &p, t);
	return (str);
}
