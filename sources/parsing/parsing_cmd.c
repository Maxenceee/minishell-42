/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffreze <ffreze@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:34:01 by ffreze            #+#    #+#             */
/*   Updated: 2023/11/02 17:11:29 by mgama            ###   ########.fr       */
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
static int	ft_parse_decomp(t_parsing_cmd *new_cmd, char* tmp_line, char *tmp)
{
	int j;
	char **tmpsplit;
	
	tmpsplit = ft_split(tmp_line, " ");
	if(!tmpsplit)
		return (MS_ERROR);
	j = count_strings(tmp_line, " ");
	new_cmd->cmd = ft_calloc((j + 1), sizeof(char *));
	if(!new_cmd->cmd)
		return (free_tab(tmpsplit), MS_ERROR);
	new_cmd->cmd[0] = ft_strdup(tmp);
	if(!new_cmd->cmd[0])
		return (free_tab(tmpsplit), free(new_cmd->cmd), MS_ERROR);
	j = -1;
	while (tmpsplit[++j])
	{
		new_cmd->cmd[j + 1] = ft_strdup(tmpsplit[j]);
		if(!new_cmd->cmd[j + 1])
			return (free_tab(tmpsplit), free_tab(new_cmd->cmd), MS_ERROR);
	}	
	return(free_tab(tmpsplit), MS_SUCCESS);
}

int	ft_compose(t_data *minishell, char *line, t_parsing_cmd *new_cmd)
{
	int	i;
	char *tmp;
	char *tmp_line;

	i = -1;
  // exemple // à supprimer
	new_cmd->cmd = ft_split_cmd(ms, line);
	while (new_cmd->cmd[++i])
		printf("[%s] ", new_cmd->cmd[i]);
	printf("\n");
	if (ft_strcmp("echo", new_cmd->cmd[0]) == 0)
		ft_builtin_echo(ms, new_cmd->cmd, 1);
  // fin exemple
	while (line[++i] != ' ' && line[i]);
	tmp = ft_strtcpy(line, i);
	if (!tmp)
		return (MS_ERROR);
	if (!line[i])
	{
		new_cmd->cmd = ft_calloc(1, sizeof(char *));
		if(!new_cmd->cmd)
			return  (MS_ERROR);
	 	new_cmd->cmd = ft_split(tmp, " ");
		if(!new_cmd->cmd)
			return  (MS_ERROR);
	 	return (free(tmp), MS_SUCCESS);
	 }
	tmp_line = ft_parse_expands(minishell, line + i);
	if(!tmp_line)
		return (free(tmp), MS_ERROR);
	if (ft_parse_decomp(new_cmd, tmp_line, tmp))
		return(free(tmp), free(tmp_line), MS_ERROR);
	return (free(tmp), MS_SUCCESS);
}

int ft_push_new_command(t_data *minishell, char *tmp_line)
{
	t_parsing_cmd	*new_cmd;
	t_parsing_cmd	*tmp;
	char			*line;

	new_cmd = ft_calloc(1, sizeof(t_parsing_cmd));
	if (!new_cmd)
		return (MS_ERROR);
  line = ft_strtrim(tmp_line, " ");
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
		tmp->next = new_cmd;
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
}
