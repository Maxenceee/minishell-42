/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:58:07 by mgama             #+#    #+#             */
/*   Updated: 2023/11/04 13:17:50 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**export_split(t_data *ms, char *token)
{
	int		i;
	int		len;
	char	**res;

	i = -1;
	len = 1;
	while (token[++i] && (ft_isalnum(token[i]) || token[i] == '_'))
		;
	if (!(token[i] == '=' || token[i] == '\0') || i == 0)
		return (NULL);
	if (token[i] == '=')
		len++;
	res = ft_calloc(len + 1, sizeof(char *));
	if (!res)
		exit_with_error(ms, MS_ERROR, MS_ALLOC_ERROR_MSG);
	res[0] = ft_strtcpy(token, i);
	if (!res[0])
		exit_with_error(ms, MS_ERROR, MS_ALLOC_ERROR_MSG);
	if (len > 1 && token + ++i)
		res[1] = ft_strdup(token + i);
	else if (len > 1)
		res[1] = ft_calloc(1, sizeof(char));
	if (len > 1 && !res[1])
	{
		free(res[0]);
		exit_with_error(ms, MS_ERROR, MS_ALLOC_ERROR_MSG);
	}
	res[len] = 0;
	return (res);
}

void	print_export_env(t_data *minishell)
{
	t_env_element	*el;

	el = minishell->env;
	while (el)
	{
		printf("declare -x %s", el->key);
		if (el->value)
			printf("=\"%s\"", el->value);
		printf("\n");
		el = el->next;
	}
}

int	ft_builtin_export(t_data *minishell, t_parsing_cmd *cmd)
{
	char	**env_e;
	int		i;

	i = 0;
	while (cmd->cmd[++i])
	{
		env_e = export_split(minishell, cmd->cmd[i]);
		if (!env_e)
		{
			ft_putfd(2, MS_ERROR_PREFIX"export: `");
			ft_putfd(2, cmd->cmd[i]);
			ft_putfd(2, "': not a valid identifier\n");
			continue ;
		}
		ft_push_env_element(minishell, ft_new_env_element(env_e[0], env_e[1]));
	}
	if (i == 1)
		print_export_env(minishell);
	else
	{
		if (minishell->envp)
			free_tab(minishell->envp);
		minishell->envp = dup_env(minishell);
	}
	return (MS_SUCCESS);
}
