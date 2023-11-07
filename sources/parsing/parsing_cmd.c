/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:34:01 by ffreze            #+#    #+#             */

/*   Updated: 2023/11/06 00:55:37 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_linked_list(t_parsing_cmd *cmd)
{
	while (cmd)
	{
		printf("- %s\n", cmd->cmd[0]);
		cmd = cmd->next;
	}
}

int realloc_doubletab(t_data *ms, t_parsing_cmd *new_cmd, int i, char ***tmp)
{
	int j;
	int k;
	char **cmdrea;

	j = 0;
	k = -1;
	if (ft_strcmp(">>", new_cmd->cmd[i]) == 0 || ft_strcmp(">", new_cmd->cmd[i]) == 0 || \
		ft_strcmp("<", new_cmd->cmd[i]) == 0 || ft_strcmp("<<", new_cmd->cmd[i]) == 0)
	{
		if (!new_cmd->cmd[i + 1])
			return (ft_cmderror(MS_ERROR_PREFIX,
				"syntax error near unexpected token `newline'", "\n"), MS_ERROR);
		while(new_cmd->cmd[j])
			j++;
		cmdrea = ft_calloc(j - 1, sizeof(char *));
		if (!cmdrea)
			exit_with_error(ms, MS_ERROR, MS_ALLOC_ERROR_MSG);
		while(++k < j)
			if(k != i && k != i + 1)
				cmdrea[k] = ft_strdup(new_cmd->cmd[k]);
		if (*tmp)
			free_tab(*tmp);
		*tmp = cmdrea;
	}
	return (MS_SUCCESS);
}

int	ft_compose(t_data *minishell, char *line, t_parsing_cmd *new_cmd)
{
	int		i;
	int		code;
	char	**tmp;

	new_cmd->cmd = ft_split_cmd(minishell, line);
	if (!new_cmd->cmd)
		exit_with_error(minishell, MS_ERROR, MS_ALLOC_ERROR_MSG);
	new_cmd->builtin = get_builtin(new_cmd->cmd[0]);
	tmp = NULL;
	i = -1;
	code = MS_SUCCESS;
	while (new_cmd->cmd[++i])
	{
		if (ft_strcmp(">>", new_cmd->cmd[i]) == 0)
			code = ft_push_new_file(new_cmd, ft_strdup(new_cmd->cmd[i + 1]), CONCAT_OUT, NULL);
		else if (ft_strcmp(">", new_cmd->cmd[i]) == 0)
			code = ft_push_new_file(new_cmd, ft_strdup(new_cmd->cmd[i + 1]), REDIR_OUT, NULL);
		else if (ft_strcmp("<", new_cmd->cmd[i]) == 0)
			code = ft_push_new_file(new_cmd, ft_strdup(new_cmd->cmd[i + 1]), REDIR_IN, NULL);
		else if (ft_strcmp("<<", new_cmd->cmd[i]) == 0)
			code = ft_push_new_file(new_cmd, NULL, CONCAT_IN, ft_strdup(new_cmd->cmd[i + 1]));
		if (code)
			exit_with_error(minishell, MS_ERROR, MS_ALLOC_ERROR_MSG);
		if (realloc_doubletab(minishell, new_cmd, i, &tmp))
			return (MS_ERROR);
	}
	if (tmp)
	{
		free_tab(new_cmd->cmd);
		new_cmd->cmd = tmp;
	}
	return (MS_SUCCESS);
}

int ft_push_new_command(t_data *minishell, char *line)
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

void	ft_destroy_parsing_files(t_parsing_cmd	*cmd)
{
	t_parsing_file	*tmp;
	t_parsing_file	*next;

	tmp = cmd->files;
	while (tmp)
	{
		next = tmp->next;
		if (tmp->file_name)
			free(tmp->file_name);
		if (tmp->here_doc_end)
			free(tmp->here_doc_end);
		free(tmp);
		tmp = next;
	}
}

void	ft_destroy_parsing_cmd(t_data *minishell)
{
	t_parsing_cmd	*tmp;
	t_parsing_cmd	*next;

	tmp = minishell->parsing_cmd;
	while (tmp)
	{
		next = tmp->next;
		free_tab(tmp->cmd);
		if (tmp->here_doc_fname)
		{
			unlink(tmp->here_doc_fname);
			free(tmp->here_doc_fname);
		}
		if (tmp->files)
			ft_destroy_parsing_files(tmp);
		free(tmp);
		tmp = next;
	}
	minishell->parsing_cmd = NULL;
	minishell->pipes = 0;
}
