/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 13:32:31 by mgama             #+#    #+#             */
/*   Updated: 2023/11/04 02:52:25 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "pcolors.h"

int	ft_putfd(int fd, char *str)
{
	return (write(fd, str, ft_strlen(str)));
}

int	ft_error(char *str)
{
	int	r;

	r = 0;
	r += write(2, B_RED, 8);
	r += write(2, str, ft_strlen(str));
	r += write(2, RESET, 4);
	return (r);
}

int	ft_warning(char *str)
{
	int	r;

	r = 0;
	r += write(2, B_YELLOW, 8);
	r += write(2, str, ft_strlen(str));
	r += write(2, RESET, 4);
	return (r);
}

int	ft_info(char *str)
{
	return (printf("%s%s%s", B_YELLOW, str, RESET));
}
