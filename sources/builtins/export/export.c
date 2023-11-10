/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:58:07 by mgama             #+#    #+#             */
/*   Updated: 2023/11/10 17:21:26 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_split_cpy(t_data *ms, char ***res, char *token, int i)
{
	int		len;

	len = 1;
	if (token[i] == '=')
		len++;
	*res = ft_calloc(len + 1, sizeof(char *));
	if (!*res)
		return (free(*res), exit_with_error(ms,
				MS_ERROR, MS_ALLOC_ERROR_MSG));
	(*res)[0] = ft_strtcpy(token, i);
	if (!(*res)[0])
		return (free(*res), exit_with_error(ms,
				MS_ERROR, MS_ALLOC_ERROR_MSG));
	if (len > 1 && token + ++i)
		(*res)[1] = ft_strdup(token + i);
	else if (len > 1)
		(*res)[1] = ft_calloc(1, sizeof(char));
	if (len > 1 && !(*res)[1])
		return (free((*res)[0]), free(*res),
			exit_with_error(ms, MS_ERROR, MS_ALLOC_ERROR_MSG));
	(*res)[len] = 0;
	return (MS_SUCCESS);
}

char	**export_split(t_data *ms, char *token)
{
	int		i;
	char	**res;

	i = 0;
	if (token[i] && (ft_isalpha(token[i]) || token[i] == '_'))
		i++;
	else
		return (NULL);
	while (token[i] && (ft_isalnum(token[i]) || token[i] == '_'))
		i++;
	if (!(token[i] == '=' || token[i] == '\0') || i == 0)
		return (NULL);
	export_split_cpy(ms, &res, token, i);
	return (res);
}

void	print_export_env(t_data *minishell)
{
	t_env_element	*el;

	el = minishell->env;
	while (el)
	{
		if (!ft_iscmp(el->key, "_"))
		{
			printf("declare -x %s", el->key);
			if (el->value)
				printf("=\"%s\"", el->value);
			printf("\n");
		}
		el = el->next;
	}
}

void	export_val(t_data *minishell, int i)
{
	if (i == 1)
		print_export_env(minishell);
	else
	{
		if (minishell->envp)
			free_tab(minishell->envp);
		minishell->envp = dup_env(minishell);
	}
}

int	ft_builtin_export(t_data *minishell, t_parsing_cmd *cmd)
{
	char	**env_e;
	int		i;
	int		code;

	i = 0;
	code = MS_SUCCESS;
	while (cmd->cmd[++i])
	{
		env_e = export_split(minishell, cmd->cmd[i]);
		if (!env_e)
		{
			ft_cmderror_ex("export: `", cmd->cmd[i],
				"': not a valid identifier\n");
			code = MS_ERROR;
			continue ;
		}
		if (!ft_iscmp(env_e[0], "_"))
			ft_push_env_element(minishell,
				ft_new_env_element(env_e[0], env_e[1]));
		free_tab(env_e);
	}
	export_val(minishell, i);
	return (code);
}
