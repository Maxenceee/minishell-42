/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:49:58 by mgama             #+#    #+#             */
/*   Updated: 2023/06/30 17:25:13 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_data	commands;
	
	(void)(argc); // temp ignoring
	(void)(argv); // temp ignoring
	ft_bzero(&commands, sizeof(t_data));
	commands.envp = envp;
	// parsing function
	fork_processes(&commands);
	return (0);
}