/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:49:58 by mgama             #+#    #+#             */
/*   Updated: 2023/11/06 00:46:28 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_name(void)
{
	printf("\n\n\n"HEADER);
	printf("___  ___ _         _       _            _  _ \n");
	printf("|  \\/  |(_)       (_)     | |          | || |\n");
	printf("| .  . | _  _ __   _  ___ | |__    ___ | || |\n");
	printf("| |\\/| || || '_ \\ | |/ __|| '_ \\  / _ \\| || |\n");
	printf("| |  | || || | | || |\\__ \\| | | ||  __/| || |\n");
	printf("\\_|  |_/|_||_| |_||_||___/|_| |_| \\___||_||_|\n\n");
	printf("\n\n"RESET);
}

char	*prompt(t_data *ms)
{
	char	*user;
	char	*tmp;

	user = NULL;
	user = ft_strjoin(user, B_GREEN);
	tmp = ft_get_env_variable(ms, "USER");
	if (tmp)
		user = ft_strjoin(user, tmp);
	user = ft_strjoin(user, "@"RESET": "MS_PROMPT_NAME);
	return (user);
}

int	ft_mainloop(t_data *minishell)
{
	int		i;
	char	*line;
	char	**pipline;
	
	minishell->prompt = prompt(minishell);
	if (!minishell->prompt)
		return (MS_ERROR);
	while (!minishell->exit)
	{
		i = -1;
		line = readline(minishell->prompt);
		if (!line)
			exit_with_code(minishell, MS_SUCCESS, "exit\n");
		if (*line == '\0')
			continue ;
		add_history(line);
		if (check_quotes(line))
		{
			ft_warning(MS_ERROR_PREFIX"invalid pattern\n");
			continue ;
		}
		pipline = ft_split(line, "|");
		free(line);
		if(!pipline)
			return (ft_error(MS_ALLOC_ERROR_MSG"split"), MS_ERROR);
		while (pipline[++i])
		{
			if (ft_push_new_command(minishell, pipline[i]))
				return (MS_ERROR);
		}
		free_tab(pipline);
		if (mini_exec(minishell))
			return (MS_ERROR);
		ft_destroy_parsing_cmd(minishell);
	}
	return (MS_SUCCESS);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	minishell;

	if (argc > 1)
		return (ft_error(MS_ERROR_PREFIX"this program does not take any aruments\n"), MS_ERROR);
	(void)(argv);
	print_name();
	ft_bzero(&minishell, sizeof(t_data));
	ft_bzero(&g_signal, sizeof(t_signal));
	setup_signals();
	ft_parse_env(&minishell, envp);
	if (ft_mainloop(&minishell))
		exit_with_code(&minishell, MS_ERROR, NULL);
	free_minishell(&minishell);
	return (0);
}
