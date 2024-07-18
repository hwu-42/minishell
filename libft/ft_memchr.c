/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:05:37 by hwu               #+#    #+#             */
/*   Updated: 2023/11/29 15:05:41 by hwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	unsigned char		cc;
	size_t				i;

	cc = (unsigned char) c;
	if (n == 0)
		return (NULL);
	str = s;
	i = 0;
	while (i < n)
	{
		if (str[i] == cc)
			break ;
		i++;
	}
	if (i == n)
		return (NULL);
	else
		return ((void *)(str + i));
}
/*
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int	main(void)
{
	char	str[100] = "fafi`$op32po\02fmsmfspfos2dfj\0wv\twfwfewf1wf23\nsb";
	int		c = 255 + 'a';
	size_t		n = 0;

	printf("%d, %c\n", c, c);
	while (n < 50)
	{
		if (ft_memchr(str, c, n) == memchr(str, c, n))
			printf("%zu: OK\n", n);
		else
			printf("%zu: bad\n", n);
		if (ft_memchr(str, c, n) == NULL)
			printf("NULL, ");
		else
			printf("%s, ", (char *)ft_memchr(str, c, n));
		if (memchr(str, c, n) == NULL)
			printf("NULL\n");
		else
			printf("%s\n", (char *)memchr(str, c, n));
		n++;
	}
	return (0);
}
*/
