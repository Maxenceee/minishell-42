/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing_cmd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:57:03 by mgama             #+#    #+#             */
/*   Updated: 2023/11/09 13:57:30 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
