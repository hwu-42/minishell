/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:06:46 by hwu               #+#    #+#             */
/*   Updated: 2024/02/19 12:56:46 by hwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*str;

	str = s;
	while (n > 0)
	{
		str[n - 1] = (unsigned char) c;
		n--;
	}
	return (s);
}
/*
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	char	buffer1[100] = "";
	char	buffer2[100] = "";
//	char	buffer3[100];
	int	c, d, e, i;

	c = 0;
	d = 'd';
	e = 'a';
//	memset(buffer3, c, 1);
	printf("buffer1:\n");
	for (i=0; i<99; i++)
		buffer1[i] = 'x';
	buffer1[99] = 0;
	printf("%s\n",buffer1);

	printf("buffer2:\n");
	for (i=0; i<100; i++)
		buffer2[i] = 'x';
	buffer2[99] = 0;
	printf("%s\n",buffer2);

	printf("if the 2 line is the same, it is right:\n");

	memset(buffer1, e, 50);
	memset(buffer1, c, 20);
	memset(buffer1, d, 10);
	for (i=0; i<100; i++)
		printf("%c", buffer1[i]);
	printf("\n");

	ft_memset(buffer2, e, 50);
	ft_memset(buffer2, c, 20);
	ft_memset(buffer2, d, 10);
	for (i=0; i<100; i++)
		printf("%c", buffer2[i]);
	printf("\n");
}
*/
