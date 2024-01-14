/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainloop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 18:15:10 by mgama             #+#    #+#             */
/*   Updated: 2024/01/14 13:43:01 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*prompt(t_data *ms)
{
	static char	*user = NULL;
	char		*tmp;

	if (!user)
	{
		user = ft_strjoin(user, B_GREEN);
		tmp = ft_get_env_variable(ms, "USER");
		if (tmp)
			user = ft_strjoin(user, tmp);
		user = ft_strjoin(user, "@"RESET": "\
HEADER"minishell$ "RESET);
	}
	else
	{
		if (get_g_signal_val(EXIT_CODE) == 0)
			ft_strlcpy(user, B_GREEN, 7);
		else
			ft_strlcpy(user, B_RED, 7);
	}
	return (user);
}

int	check_syntax(char **pipline, int i, int j)
{
	char	*tmp;

	tmp = ft_strtrim(pipline[i], " ");
	if (ft_strlen(tmp) == 0 && !pipline[i + 1] && i == 0 && j == 0)
		return (free(tmp), MS_NO_ERROR);
	else if (ft_strlen(tmp) == 0 || (!pipline[i + 1] && j > i))
	{
		set_g_signal_val(EXIT_CODE, 2);
		return (ft_sntxerror(MS_SYNTAX_ERROR, "|"),
			free(tmp), MS_ERROR);
	}
	free(tmp);
	return (MS_SUCCESS);
}

int	run_cmd(t_data *minishell, char *line)
{
	int		i;
	int		j;
	int		code;
	char	**pipline;

	i = -1;
	code = 0;
	pipline = ft_pipe_split(ft_parse_expands(minishell, line, 1), &j);
	free(line);
	if (!pipline)
		exit_with_error(minishell, MS_ERROR, MS_ALLOC_ERROR_MSG);
	while (pipline[++i])
	{
		code = check_syntax(pipline, i, j);
		if (!code)
			code = ft_push_new_command(minishell, pipline[i]);
		if (code)
			break ;
	}
	if (i == 0 && !code)
		code = check_syntax(pipline, i, j);
	free_tab(pipline);
	if (!code && mini_exec(minishell))
		return (MS_ERROR);
	return (MS_SUCCESS);
}

int	ft_mainloop(t_data *minishell)
{
	char	*line;

	while (!minishell->exit)
	{
		setup_signals();
		minishell->prompt = prompt(minishell);
		if (!minishell->prompt)
			return (MS_ERROR);
		line = readline(minishell->prompt);
		if (!line)
			exit_with_code(minishell, MS_SUCCESS, "exit\n");
		if (*line == '\0')
			continue ;
		add_history(line);
		if (check_quotes(line))
		{
			ft_cmderror("invalid pattern", "\n");
			set_g_signal_val(EXIT_CODE, 2);
			continue ;
		}
		run_cmd(minishell, line);
		ft_destroy_parsing_cmd(minishell);
	}
	return (MS_SUCCESS);
}
