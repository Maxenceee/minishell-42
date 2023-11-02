/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 15:34:01 by ffreze            #+#    #+#             */
/*   Updated: 2023/11/02 03:59:24 by mgama            ###   ########.fr       */
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

int	ft_compose(t_data *ms, char *line, t_parsing_cmd *new_cmd)
{
	int	i;
	char *tmp;

	i = -1;
	// while (line[++i] != '>' && line[++i] != '<' && line[++i])
	// 	;
	// tmp = ft_strtcpy(line, i);
	// if (!tmp)
	// 	return (MS_ERROR);
	new_cmd->cmd = ft_split(ft_parse_expands(ms, line), " ");
	while (new_cmd->cmd[++i])
	{
		printf("[%s] ", new_cmd->cmd[i]);
	}
	printf("\n");
	if (ft_strcmp(new_cmd->cmd[0], "grep") == 0)
	{
		// new_cmd->files = ft_calloc(1, sizeof(t_parsing_file));
		// new_cmd->files->file_name = "oui";
		// new_cmd->type = O_APPEND;
		// new_cmd->files->next = ft_calloc(1, sizeof(t_parsing_file));
		// new_cmd->files->next->file_name = "non";
		// new_cmd->type = O_APPEND;
	}
	// free(tmp);
	// if(!new_cmd->cmd)
	// 	return (MS_ERROR);
	// new_cmd->line = ft_strdup(line);
	// if(!new_cmd->line)
	// 	return (free_tab(new_cmd->cmd), MS_ERROR);
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
		tmp->next = new_cmd;
	return (MS_SUCCESS);
}

int ft_interpretor_line(t_data *minishell)
{
	int i;

	i = -1;
	//envoyer a l'execve minishell->cmd
	// si il y a + d'un separateur juste cree les premiers ficher et de rien faire dedans prendre les autre 
	// while(line)
	// {
		
	// }
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
