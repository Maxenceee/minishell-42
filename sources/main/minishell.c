/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:49:58 by mgama             #+#    #+#             */
/*   Updated: 2023/11/02 18:12:35 by mgama            ###   ########.fr       */
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

	user = NULL;
	user = ft_strjoin(user, ft_strdup(B_GREEN));
	user = ft_strjoin(user, ft_get_env_variable(ms, "USER"));
	user = ft_strjoin(user, "@"RESET": "MS_PROMPT_NAME);
	return (user);
}

int	ft_mainloop(t_data *minishell)
{
	int		i;
	char	*line;
	char	*pt;
	char	**pipline;
	
	pt = prompt(minishell);
	if (!pt)
		return (MS_ERROR);
	while (!minishell->exit)
	{
		i = -1;
		line = readline(pt);
		add_history(line);
		pipline = ft_split(line, "|");
		if(!pipline)
			return (ft_error(MS_ALLOC_ERROR_MSG), MS_ERROR);
		while (pipline[++i])
		{
			if (ft_push_new_command(minishell, pipline[i]))
				return (ft_error(MS_ALLOC_ERROR_MSG), MS_ERROR);
		}
		if (fork_processes(minishell))
			return (MS_ERROR);
		// print_linked_list(minishell->parsing_cmd);
		ft_destroy_parsing_cmd(minishell);
		free(line);
	}
	free(pt);
	return (MS_SUCCESS);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_data	minishell;

	(void)(argc);
	(void)(argv);
	ft_bzero(&minishell, sizeof(t_data));
	minishell.in = dup(STDIN_FILENO);
	minishell.out = dup(STDOUT_FILENO);
	print_name();
	ft_parse_env(&minishell, envp);
	// print_env(&minishell);
	// dup_env(&minishell);
	// return 1;
	ft_mainloop(&minishell);
	free_minishell(&minishell);
	return (0);
}