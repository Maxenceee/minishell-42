/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 00:07:56 by mgama             #+#    #+#             */
/*   Updated: 2023/11/01 00:17:15 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*my_readline(char *prompt)
{
	char	c;
	char	*res;

	c = 0;
	res = NULL;
	printf("%s", prompt);
	fflush(NULL);
	while (c != 10)
	{
		read(0, &c, 1);
		res = ft_strjoin_char(res, c);
	}
	printf("readline res: %s\n", res);
	return (res);
}
