/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:49:58 by mgama             #+#    #+#             */
/*   Updated: 2023/07/08 10:47:32 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	minishell;
	
	(void)(argc); // temp ignoring
	(void)(argv); // temp ignoring
	ft_bzero(&minishell, sizeof(t_data));
	minishell.envp = envp;
	minishell.in = dup(STDIN);
	minishell.out = dup(stdout);
	reset_fds(&minishell);
	printf("%d\n", minishell.exit);
	// parsing function
	// fork_processes(&minishell);
	return (0);
}