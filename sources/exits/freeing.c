/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 14:56:44 by mgama             #+#    #+#             */
/*   Updated: 2023/11/09 16:15:53 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_minishell(t_data *minishell)
{
	free_env(minishell);
	if (minishell->envp)
		free_tab(minishell->envp);
	if (minishell->parsing_cmd)
		ft_destroy_parsing_cmd(minishell);
	if (minishell->prompt)
		free(minishell->prompt);
	if (minishell->pwd)
		free(minishell->pwd);
}
