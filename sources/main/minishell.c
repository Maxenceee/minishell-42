/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:49:58 by mgama             #+#    #+#             */
/*   Updated: 2023/12/29 16:04:28 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

uint32_t	g_signal = 0;

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

	(void)(argv);
	if (argc > 1)
		return (ft_error(MS_ERROR_PREFIX, "this program \
does not take any aruments\n"), MS_ERROR);
	if (isatty(STDOUT_FILENO))
		print_name();
	ft_bzero(&minishell, sizeof(t_data));
	ft_parse_env(&minishell, envp);
	if (ft_mainloop(&minishell))
		exit_with_code(&minishell, MS_ERROR, NULL);
	free_minishell(&minishell);
	return (0);
}
