/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:03:04 by mgama             #+#    #+#             */
/*   Updated: 2023/11/09 14:01:50 by mgama            ###   ########.fr       */
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

int	parse_redirection(t_parsing_cmd *cmd, int *i, char ***tmp)
{
	int	code;

	code = MS_SUCCESS;
	if ((ft_iscmp(">>", cmd->cmd[*i]) || ft_iscmp(">", cmd->cmd[*i])
			|| ft_iscmp("<", cmd->cmd[*i]) || ft_iscmp("<<", cmd->cmd[*i]))
		&& !cmd->cmd[*i + 1])
		return (ft_cmderror(MS_SYNTAX_ERROR, ""), MS_ERROR);
	if (ft_iscmp(">>", cmd->cmd[*i]))
		code = ft_push_new_file(cmd, ft_strdup(cmd->cmd[*i + 1]), C_OUT, 0);
	else if (ft_iscmp(">", cmd->cmd[*i]))
		code = ft_push_new_file(cmd, ft_strdup(cmd->cmd[*i + 1]), R_OUT, 0);
	else if (ft_iscmp("<", cmd->cmd[*i]))
		code = ft_push_new_file(cmd, ft_strdup(cmd->cmd[*i + 1]), R_IN, 0);
	else if (ft_iscmp("<<", cmd->cmd[*i]))
		code = ft_push_new_file(cmd, 0, C_IN, ft_strdup(cmd->cmd[*i + 1]));
	else
	{
		*tmp = ft_joinf_tab(*tmp, cmd->cmd[*i]);
		if (!*tmp)
			return (MS_ERROR);
		return (code);
	}
	(*i)++;
	return (code);
}

int	ft_compose(t_data *minishell, char *line, t_parsing_cmd *new_cmd)
{
	int		i;
	int		code;
	char	**tmp;

	tmp = NULL;
	new_cmd->cmd = ft_split_cmd(line);
	if (!new_cmd->cmd)
		exit_with_error(minishell, MS_ERROR, MS_ALLOC_ERROR_MSG);
	new_cmd->builtin = get_builtin(new_cmd->cmd[0]);
	i = -1;
	while (new_cmd->cmd[++i])
	{
		code = parse_redirection(new_cmd, &i, &tmp);
		if (code)
			exit_with_error(minishell, MS_ERROR, MS_ALLOC_ERROR_MSG);
	}
	if (tmp)
	{
		free_tab(new_cmd->cmd);
		new_cmd->cmd = tmp;
	}
	return (MS_SUCCESS);
}

int	ft_push_new_command(t_data *minishell, char *line)
{
	t_parsing_cmd	*new_cmd;
	t_parsing_cmd	*tmp;

	new_cmd = ft_calloc(1, sizeof(t_parsing_cmd));
	if (!new_cmd)
		exit_with_error(minishell, MS_ERROR, MS_ALLOC_ERROR_MSG);
	if (ft_compose(minishell, line, new_cmd))
		return (free(new_cmd), MS_ERROR);
	tmp = minishell->parsing_cmd;
	while (tmp)
	{
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (!minishell->parsing_cmd)
		minishell->parsing_cmd = new_cmd;
	else
	{
		new_cmd->prev = tmp;
		tmp->next = new_cmd;
	}
	minishell->pipes++;
	return (MS_SUCCESS);
}

int	ft_push_new_file(t_parsing_cmd *cmd, char *file_name,
	t_parsing_token type, char *here_doc_end)
{
	t_parsing_file	*new_file;
	t_parsing_file	*tmp;

	new_file = ft_calloc(1, sizeof(t_parsing_file));
	if (!new_file)
		return (MS_ERROR);
	new_file->file_name = file_name;
	new_file->type = type;
	new_file->here_doc_end = here_doc_end;
	tmp = cmd->files;
	while (tmp)
	{
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (!cmd->files)
		cmd->files = new_file;
	else
		tmp->next = new_file;
	return (MS_SUCCESS);
}
