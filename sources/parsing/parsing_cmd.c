/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:34:01 by ffreze            #+#    #+#             */
/*   Updated: 2023/11/05 19:47:28 by mgama            ###   ########.fr       */
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

static int	ft_parse_decomp(t_parsing_cmd *new_cmd, int i)
{
	// // if(new_cmd->files->type)
	// // 	new_cmd->files->file_name = ft_strdup(new_cmd->cmd[i-1]);
	// if (!new_cmd->files->file_name)
	// 	return (MS_ERROR);
	// return (MS_SUCCESS);
}
 
int    ft_push_new_file(t_parsing_cmd *cmd, char *file_name, t_parsing_token type)
{
    t_parsing_file    *new_file;
    t_parsing_file    *tmp;

    new_file = ft_calloc(1, sizeof(t_parsing_file));
    if (!new_file)
        return (MS_ERROR);
    new_file->file_name = file_name;
    new_file->type = type;
    tmp = cmd->files;
	printf("file name :%s\n", file_name);
	if (type == CONCAT_OUT)
		printf("type : concat out");
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

int	ft_compose(t_data *minishell, char *line, t_parsing_cmd *new_cmd)
{
	int	i;
	i = -1;
	new_cmd->cmd = ft_split_cmd(minishell, line);
// exemple 
	while (new_cmd->cmd[++i])
		printf("[%s] ", new_cmd->cmd[i]);
	printf("\n");
// fin exemple
	i = -1;
	// if (ft_strcmp("echo", new_cmd->cmd[0]) == 0)
	// 	ft_builtin_echo(minishell, new_cmd->cmd + 1, 1);
	while (new_cmd->cmd[++i])
	{
		if (ft_strcmp(">>", new_cmd->cmd[i]) == 0)
			ft_push_new_file(new_cmd, new_cmd->cmd[i + 1], CONCAT_OUT);
		else if (ft_strcmp(">", new_cmd->cmd[i]) == 0)
			ft_push_new_file(new_cmd, new_cmd->cmd[i + 1], REDIR_OUT);
		else if (ft_strcmp("<", new_cmd->cmd[i]) == 0)
			ft_push_new_file(new_cmd, new_cmd->cmd[i + 1], REDIR_IN);
		else if (ft_strcmp("<<", new_cmd->cmd[i]) == 0)
			ft_push_new_file(new_cmd, new_cmd->cmd[i + 1], CONCAT_IN);
		// printf("%d\n", i);
		// ft_parse_decomp(new_cmd, i);
	}
	return (MS_SUCCESS);
}

int ft_push_new_command(t_data *minishell, char *line)
{
	t_parsing_cmd	*new_cmd;
	t_parsing_cmd	*tmp;

	new_cmd = ft_calloc(1, sizeof(t_parsing_cmd));
	if (!new_cmd)
		return (MS_ERROR);
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

void	ft_destroy_parsing_cmd(t_data *minishell)
{
	t_parsing_cmd	*tmp;
	t_parsing_cmd	*next;

	tmp = minishell->parsing_cmd;
	while (tmp)
	{
		next = tmp->next;
		free_tab(tmp->cmd);
		free(tmp);
		tmp = next;
	}
	minishell->parsing_cmd = NULL;
	minishell->pipes = 0;
}
