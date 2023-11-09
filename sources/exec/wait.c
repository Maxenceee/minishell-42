/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 19:14:46 by mgama             #+#    #+#             */
/*   Updated: 2023/11/08 23:34:12 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_signal_interrupt(int status, int is_last_child)
{
	if (WTERMSIG(status) == SIGINT)
		ft_putfd(STDOUT_FILENO, "\n");
	if (WTERMSIG(status) == SIGQUIT && is_last_child)
		ft_putfd(STDOUT_FILENO, "Quit\n");
	return (128 + WTERMSIG(status));
}

int	wait_process(pid_t pid, int last)
{
	int	status;
	int	res;

	if (pid == -1)
		return (EXIT_FAILURE);
	res = EXIT_SUCCESS;
	if (waitpid(pid, &status, 0) == -1)
		return (ft_cmderror(MS_ERROR_PREFIX, "wait", "\n"), MS_ERROR);
	if (WIFSIGNALED(status))
		res = handle_signal_interrupt(status, last);
	else if (WIFEXITED(status))
		res = WEXITSTATUS(status);
	set_g_signal_val(EXIT_CODE, res);
	return (res);
}

void	wait_all_process(t_data *ms)
{
	int				status;
	t_parsing_cmd	*cmd;

	cmd = ms->parsing_cmd;
	while (cmd)
	{
		status = wait_process(cmd->pid, cmd->next == NULL);
		cmd = cmd->next;
	}
	set_g_signal_val(EXIT_CODE, status);
}
