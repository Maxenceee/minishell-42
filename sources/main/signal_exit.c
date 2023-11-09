/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:59:38 by mgama             #+#    #+#             */
/*   Updated: 2023/11/09 13:59:45 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_g_signal_val(int flag)
{
	if (flag == EXIT_CODE)
		return ((g_signal << 24) >> 24);
	else if (flag == STOP_HEREDOC)
		return ((g_signal & flag) >> 8);
	else if (flag == IN_CMD)
		return ((g_signal & flag) >> 9);
	else if (flag == IN_HERE_DOC)
		return ((g_signal & flag) >> 10);
	return (0);
}

void	set_g_signal_val(int flag, int val)
{
	if (flag == EXIT_CODE)
		g_signal = ((g_signal >> 8) << 8) | val;
	else if (flag == STOP_HEREDOC)
	{
		g_signal &= ~(1 << 8);
		g_signal |= val << 8;
	}
	else if (flag == IN_CMD)
	{
		g_signal &= ~(1 << 9);
		g_signal |= val << 9;
	}
	else if (flag == IN_HERE_DOC)
	{
		g_signal &= ~(1 << 10);
		g_signal |= val << 10;
	}
}
