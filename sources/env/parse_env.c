/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 16:17:19 by mgama             #+#    #+#             */
/*   Updated: 2023/11/04 20:35:52 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_element	*ft_new_env_element(char *key, char *value)
{
	t_env_element	*env_e;

	if (!key)
		return (ft_error("Error: missing key for env variable.\n"), NULL);
	env_e = ft_calloc(1, sizeof(t_env_element));
	if (!env_e)
		return (NULL);
	env_e->key = ft_strdup(key);
	if (!env_e->key)
		return (free(env_e), NULL);
	if (value)
	{
		env_e->value = ft_strdup(value);
		if (!env_e->value)
			return (free(env_e->key), free(env_e), NULL);
	}
	return (env_e);
}

t_env_element	*ft_new_env_element_fromline(char *line)
{
	char			**splt;
	t_env_element	*env_e;

	splt = ft_split(line, "=");
	if (!splt)
		return (NULL);
	env_e = ft_new_env_element(splt[0], splt[1]);
	free_tab(splt);
	return (env_e);
}

int	parse_env_pwd(t_data *ms)
{
	char	*tmp;

	tmp = ft_get_env_variable(ms, "PWD");
	if (!tmp)
	{
		update_wd(ms);
		tmp = ft_get_env_variable(ms, "PWD");
	}
	ms->pwd = ft_strdup(tmp);
	return (MS_SUCCESS);
}

int	increment_shelllvl(t_data *ms)
{
	char	*shlvl;

	shlvl = ft_get_env_variable(ms, "SHLVL");
	shlvl = ft_itoa(ft_atoi(shlvl) + 1);
	ft_push_env_element(ms, ft_new_env_element( "SHLVL", shlvl));
	free(shlvl);
	return (MS_SUCCESS);
}

int	ft_parse_env(t_data *minishell, char **envp)
{
	int		i;

	i = -1;
	while (envp[++i])
	{
		if (ft_push_env_element(minishell,
				ft_new_env_element_fromline(envp[i])))
			return (ft_error(MS_ALLOC_ERROR_MSG), MS_ERROR);
	}
	parse_env_pwd(minishell);
	increment_shelllvl(minishell);
	minishell->envp = dup_env(minishell);
	return (MS_SUCCESS);
}
