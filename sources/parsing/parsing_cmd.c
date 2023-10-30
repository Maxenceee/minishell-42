/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffreze <ffreze@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:34:01 by ffreze            #+#    #+#             */
/*   Updated: 2023/10/30 16:57:38 by ffreze           ###   ########.fr       */
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

int	ft_compose(char *line, t_parsing_cmd *new_cmd)
{
	int	i;

	i = -1;
	new_cmd->cmd = ft_split(line, " \t");
	if(!new_cmd->cmd)
		return (MS_ERROR);
	new_cmd->line = ft_strdup(line);
	if(!new_cmd->line)
		return (free_tab(new_cmd->cmd), MS_ERROR);
}

int ft_push_new_command(t_data *minishell, char *line)
{
	t_parsing_cmd	*new_cmd;
	t_parsing_cmd	*tmp;

	new_cmd = ft_calloc(1, sizeof(t_parsing_cmd));
	if (!new_cmd)
		return (MS_ERROR);
	if (ft_compose(line, new_cmd))
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
