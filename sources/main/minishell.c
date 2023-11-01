/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffreze <ffreze@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:49:58 by mgama             #+#    #+#             */
/*   Updated: 2023/10/30 15:20:59 by ffreze           ###   ########.fr       */
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

int	main(int argc, char *argv[], char *envp[])
{
	t_data	minishell;

	(void)(argc);
	(void)(argv);
	ft_bzero(&minishell, sizeof(t_data));
	minishell.in = dup(STDIN);
	minishell.out = dup(STDOUT);
	reset_fds(&minishell);
	print_name();
	ft_parse_env(&minishell, envp);
	// print_env(&minishell);
	ft_mainloop(&minishell);
	free_minishell(&minishell);
	return (0);
}