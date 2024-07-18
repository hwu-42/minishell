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

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;

	if (n == 0)
		return (0);
	str1 = s1;
	str2 = s2;
	while (*str1 == *str2 && n-- > 1)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
/*
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define num 10

int	main(void)
{
	char	s1[100] = "faxfi1p32pofmsmfspfos2dfj\0x1v\twfwfewf1wf23\nsb";
	char	s2[100] = "faxfi1p32pofmsmfspfos2dfj\0x2v";
	int	i;
	int same = 1;

	printf("%d\n", ft_memcmp(s1, s2, num));

	for(i=0; i<101; i++)
	{
		printf("%d, %d\n",memcmp(s1, s2, i), ft_memcmp(s1, s2, i));
		if (memcmp(s1, s2, i) != ft_memcmp(s1, s2, i))
			same = 0;
	}
	if (same == 1)
		printf("returned value is the same with memcmp.\n");
	else
		printf("returned value is wrong!\n");
	return (0);
}
*/
