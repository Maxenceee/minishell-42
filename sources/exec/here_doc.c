/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:34:34 by mgama             #+#    #+#             */
/*   Updated: 2023/11/06 00:19:06 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_here_doc_fname()
{
	static int	i = 0;
	char		*num;
	char		*file_name;

	num = ft_itoa(i++);
	file_name = ft_strjoin(NULL, ".objs/.tmp_hd_file");
	file_name = ft_strjoin(file_name, num);
	free(num);
	return (file_name);
}

int	create_heredoc(t_data *ms, t_parsing_file *f, char *path)
{
	int		fd;
	char	*line;

	g_signal.stop_heredoc = 0;
	g_signal.in_here_doc = 1;
	fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (ft_putfd(STDERR_FILENO, MS_ERROR_PREFIX"heredoc open: "),
			perror(""), MS_ERROR);
	line = readline(MS_HEREDOC_MSG);
	while (line && ft_strncmp(f->here_doc_end, line, ft_strlen(f->here_doc_end))
		&& !g_signal.stop_heredoc)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		line = readline(MS_HEREDOC_MSG);
	}
	if (g_signal.stop_heredoc || !line)
		return (MS_ERROR);
	free(line);
	close(fd);
	g_signal.in_here_doc = 0;
	return (MS_SUCCESS);
}

int	open_heredoc(t_data *ms, t_parsing_cmd *cmd)
{
	t_parsing_file	*f;

	f = cmd->files;
	while (f)
	{
		if (f->type == CONCAT_IN)
		{
			if (cmd->here_doc_fname)
			{
				unlink(cmd->here_doc_fname);
				free(cmd->here_doc_fname);
			}
			cmd->here_doc_fname = new_here_doc_fname();
			if (create_heredoc(ms, f, cmd->here_doc_fname))
			{
				g_signal.exit_code = MS_ERROR;
				return (MS_NO_ERROR);
			}
				
		}
		f = f->next;
	}
	return (MS_SUCCESS);
}

int	check_fd_heredoc(t_parsing_cmd *cmd, int pip[2])
{
	if (cmd->here_doc_fname)
	{
		close(pip[0]);
		return (open(cmd->here_doc_fname, O_RDONLY));
	}
	return (pip[0]);
}
