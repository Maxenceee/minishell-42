/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 18:21:50 by mgama             #+#    #+#             */
/*   Updated: 2023/11/09 14:43:51 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_infile(char *file_name)
{
	int	fd;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (ft_cmderror(file_name, ": "),
			perror(""), MS_ERROR);
	if (fd > 0 && dup2(fd, STDIN_FILENO) < 0)
		return (ft_error(MS_ERROR_PREFIX, MS_PIPE_ERROR), MS_ERROR);
	if (fd > 0)
		close(fd);
	return (MS_SUCCESS);
}

int	handle_outfile(t_parsing_file *f, char *file_name)
{
	int	fd;

	if (f->type == R_OUT)
		fd = open(file_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	else
		fd = open(file_name, O_CREAT | O_RDWR | O_APPEND, 0644);
	if (fd < 0)
		return (ft_cmderror(file_name, ": "),
			perror(""), MS_ERROR);
	if (fd > 0 && dup2(fd, STDOUT_FILENO) < 0)
		return (ft_error(MS_ERROR_PREFIX, MS_PIPE_ERROR), MS_ERROR);
	if (fd > 0)
		close(fd);
	return (MS_SUCCESS);
}

int	open_fdinout(t_parsing_cmd *cmd)
{
	t_parsing_file	*f;

	f = cmd->files;
	while (f)
	{
		if (f->type == R_IN)
		{
			if (handle_infile(f->file_name))
				return (MS_ERROR);
		}
		else if (f->type == R_OUT || f->type == C_OUT)
		{
			if (handle_outfile(f, f->file_name))
				return (MS_ERROR);
		}
		else if (f->type == C_IN)
		{
			if (handle_infile(cmd->here_doc_fname))
				return (MS_ERROR);
		}
		f = f->next;
	}
	return (MS_SUCCESS);
}

int	dup_cmd(t_data *minishell, t_parsing_cmd *cmd, int pip[2])
{
	if (cmd->prev && dup2(cmd->fin, STDIN_FILENO) < 0)
		return (MS_ERROR);
	close(pip[0]);
	if (cmd->next && dup2(pip[1], STDOUT_FILENO) < 0)
		return (MS_ERROR);
	close(pip[1]);
	if (cmd->prev)
		close(cmd->fin);
	handle_cmd(minishell, cmd);
	return (MS_SUCCESS);
}
