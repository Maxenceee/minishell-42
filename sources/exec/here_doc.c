/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 18:34:34 by mgama             #+#    #+#             */
/*   Updated: 2023/12/19 13:09:35 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*new_here_doc_fname(void)
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

int	str_equal(const char *str1, const char *str2)
{
	size_t	size;

	if (!str1 || !str2)
		return (0);
	size = ft_strlen(str1);
	if (size != ft_strlen(str2))
		return (0);
	return (ft_strncmp(str1, str2, size) == 0);
}

int	create_heredoc(t_data *ms, t_parsing_file *f, char *path)
{
	int			fd;
	char		*line;
	char		*pline;
	const char	*hd_pt = B_PURPLE"> "RESET;

	fd = open(path, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd < 0)
		return (ft_cmderror("heredoc open: ", ""),
			perror(""), MS_ERROR);
	line = readline(hd_pt);
	dprintf(2, "%s while is good %d\n", line, line && ft_strcmp(f->here_doc_end, line));
	fflush(stderr);
	while (line && !str_equal(line, f->here_doc_end))
	{
		dprintf(2, "ff %s\n", line);
		pline = ft_parse_expands(ms, line, 0);
		dprintf(2, "pline: %s\n", pline);
		free(line);
		// ft_replace(pline, -2, '\'');
		// ft_replace(pline, -3, '\"');
		// ft_putfd(fd, pline);
		// ft_putfd(fd, "\n");
		free(pline);
		line = readline(hd_pt);
		dprintf(2, "after line (%s)\n", line);
		fflush(stderr);
	}
	free(line);
	close(fd);
	free_env(ms);
	clear_history();
	exit(MS_SUCCESS);
}

int	handle_here_doc(t_data *ms, t_parsing_cmd *cmd, t_parsing_file *f)
{
	pid_t	pid;
	int		status;

	pid = fork();
	setup_hd_signals(pid);
	if (pid == -1)
		exit_with_error(ms, MS_ERROR, MS_FORK_ERROR);
	if (pid == 0)
	{
		create_heredoc(ms, f, cmd->here_doc_fname);
	}
	else
	{
		status = wait_process(pid, 1);
		setup_signals();
		dprintf(2, "after waiting for hd\n");
		fflush(stderr);
		if (status != EXIT_SUCCESS)
			return (MS_NO_ERROR);
	}
	return (MS_SUCCESS);
}

int	open_heredoc(t_data *ms, t_parsing_cmd *cmd)
{
	t_parsing_file	*f;
	int				exit_code;

	f = cmd->files;
	while (f)
	{
		if (f->type == C_IN)
		{
			if (cmd->here_doc_fname)
			{
				unlink(cmd->here_doc_fname);
				free(cmd->here_doc_fname);
			}
			cmd->here_doc_fname = new_here_doc_fname();
			exit_code = handle_here_doc(ms, cmd, f);
			if (exit_code)
				return (exit_code);
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
