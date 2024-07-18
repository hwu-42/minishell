/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 08:18:09 by hwu               #+#    #+#             */
/*   Updated: 2023/12/01 08:18:11 by hwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		write(fd, "-2147483648", 11);
	else
	{
		if (n < 0)
		{
			write(fd, "-", 1);
			ft_putnbr_fd(-n, fd);
		}
		else if (n < 10)
		{
			n = n + '0';
			write(fd, &n, 1);
		}
		else
		{
			ft_putnbr_fd(n / 10, fd);
			n = n % 10 + '0';
			write(fd, &n, 1);
		}
	}
}
/*
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>


int	main(void)
{
	int		j = 1;
	int		i = 1;

	for(i=-11;i<19;i++)
	{
		ft_putnbr_fd(i, j);
		write(1, "\n", 1);
	}

	i = INT_MAX;
	ft_putnbr_fd(i, j);
	write(1, "\n", 1);

	i = INT_MIN;
	ft_putnbr_fd(i, j);
	write(1, "\n", 1);

	return (0);
}
*/
