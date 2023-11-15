/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:03:04 by mgama             #+#    #+#             */
/*   Updated: 2023/11/15 17:21:22 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redir_token(char *cmd)
{
	return (ft_iscmp(">>", cmd)
		|| ft_iscmp(">", cmd)
		|| ft_iscmp("<", cmd)
		|| ft_iscmp("<<", cmd));
}

int	verif_redir(t_parsing_cmd *cmd, int *i)
{
	const int	a = is_redir_token(cmd->cmd[*i]);

	if (a && !cmd->cmd[*i + 1])
		return (ft_sntxerror(MS_SYNTAX_ERROR, '\n'), MS_ERROR);
	else if (a && is_redir_token(cmd->cmd[*i + 1]))
		return (ft_sntxerror(MS_SYNTAX_ERROR, cmd->cmd[*i + 1][0]), MS_ERROR);
	if (a && ft_strlen(cmd->cmd[*i + 1]) == 0)
		return (ft_cmderror(MS_AMBIGUOUS_ERROR, ""), MS_ERROR);
	return (MS_SUCCESS);
}

int	parse_redirection(t_data *ms, t_parsing_cmd *cmd, int *i, char ***tmp)
{
	int	code;

	code = MS_SUCCESS;
	if (verif_redir(cmd, i))
		return (MS_ERROR);
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
		ft_replace(cmd->cmd[*i], -5, '>');
		ft_replace(cmd->cmd[*i], -6, '<');
		*tmp = ft_joinf_tab(*tmp, cmd->cmd[*i]);
		if (!*tmp)
			exit_with_error(ms, MS_ERROR, MS_ALLOC_ERROR_MSG);
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
	i = -1;
	while (new_cmd->cmd[++i])
	{
		if (!new_cmd->cmd[i])
			return (MS_SUCCESS);
		code = parse_redirection(minishell, new_cmd, &i, &tmp);
		if (code)
			return (set_g_signal_val(EXIT_CODE, 1), code);
	}
	if (tmp)
	{
		free_tab(new_cmd->cmd);
		new_cmd->cmd = tmp;
	}
	new_cmd->builtin = get_builtin(new_cmd->cmd[0]);
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
