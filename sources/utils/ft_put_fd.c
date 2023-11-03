/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_fd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 00:40:06 by mgama             #+#    #+#             */
/*   Updated: 2023/11/04 00:40:24 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbr_fd(int fd, int n)
{
	long long	j;

	j = (long long)n;
	if (j < 0)
	{
		ft_putchar_fd('-', fd);
		j *= -1;
	}
	if (j < 10)
		ft_putchar_fd(j + '0', fd);
	if (j >= 10)
	{
		ft_putnbr_fd(j / 10, fd);
		ft_putchar_fd((j % 10) + '0', fd);
	}
}
