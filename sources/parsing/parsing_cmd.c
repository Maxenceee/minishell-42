/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:34:01 by ffreze            #+#    #+#             */
/*   Updated: 2023/11/04 19:08:23 by mgama            ###   ########.fr       */
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

// static int	ft_parse_decomp(t_parsing_cmd *new_cmd, char* tmp_line, char *tmp)
// {
// 	int j;
// 	char **tmpsplit;
	
// 	tmpsplit = ft_split(tmp_line, " ");
// 	if(!tmpsplit)
// 		return (MS_ERROR);
// 	j = count_strings(tmp_line, " ");
// 	new_cmd->cmd = ft_calloc((j + 1), sizeof(char *));
// 	if(!new_cmd->cmd)
// 		return (free_tab(tmpsplit), MS_ERROR);
// 	new_cmd->cmd[0] = ft_strdup(tmp);
// 	if(!new_cmd->cmd[0])
// 		return (free_tab(tmpsplit), free(new_cmd->cmd), MS_ERROR);
// 	j = -1;
// 	while (tmpsplit[++j])
// 	{
// 		new_cmd->cmd[j + 1] = ft_strdup(tmpsplit[j]);
// 		if(!new_cmd->cmd[j + 1])
// 			return (free_tab(tmpsplit), free_tab(new_cmd->cmd), MS_ERROR);
// 	}	
// 	return(free_tab(tmpsplit), MS_SUCCESS);
// }

int	ft_compose(t_data *minishell, char *line, t_parsing_cmd *new_cmd)
{
	int	i;
	// char *tmp;
	// char *tmp_line;

	i = -1;
	new_cmd->cmd = ft_split_cmd(minishell, line);
	new_cmd->builtin = get_builtin(new_cmd->cmd[0]);
// exemple 
	while (new_cmd->cmd[++i])
		printf("[%s] ", new_cmd->cmd[i]);
	printf("\n");
	// if (ft_strcmp("cat", new_cmd->cmd[0]) == 0 && new_cmd->cmd[1])
	// {
	// 	ft_push_new_file(new_cmd, "oui", CONCAT_OUT, NULL);
	// 	new_cmd->cmd[1] = 0;
	// }	
// fin exemple
	// while (line[++i] != ' ' && line[i]);
	// tmp = ft_strtcpy(line, i);
	// if (!tmp)
	// 	return (MS_ERROR);
	// if (!line[i])
	// {
	// 	new_cmd->cmd = ft_calloc(1, sizeof(char *));
	// 	if(!new_cmd->cmd)
	// 		return  (MS_ERROR);
	//  	new_cmd->cmd = ft_split(tmp, " ");
	// 	if(!new_cmd->cmd)
	// 		return  (MS_ERROR);
	//  	return (free(tmp), MS_SUCCESS);
	//  }
	// tmp_line = ft_parse_expands(minishell, line + i);
	// if(!tmp_line)
	// 	return (free(tmp), MS_ERROR);
	// if (ft_parse_decomp(new_cmd, tmp_line, tmp))
	// 	return(free(tmp), free(tmp_line), MS_ERROR);
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
