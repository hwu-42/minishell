/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 16:22:07 by hwu               #+#    #+#             */
/*   Updated: 2023/11/28 16:22:10 by hwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
/*
#include <bsd/string.h>

size_t	ft_strlcpy(char *dest, char *src, size_t size)
{
	return (strlcpy(dest, src, size));
}
*/

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	count;
	size_t	i;

	count = ft_strlen(src);
	if (size == 0)
		return (count);
	i = 1;
	while (i < size && *src != 0)
	{
		*dest = *src;
		src++;
		dest++;
		i++;
	}
	*dest = 0;
	return (count);
}
/*
#include <stdio.h>
#include <string.h>
#include <bsd/string.h>
int	main(void)
{
	char	string1[11] = "abcdefghij";
	char	string2[7] = "\00001234";
	char	string3[11] = "abcdefghij";
	char	string4[7] = "\00001234";
//	size_t	size;
	int		i;
	int		j;

	printf("-10\n");
	printf("%zu, ", ft_strlcpy(string1, string2, -10));
	printf("%zu\n", strlcpy(string3, string4, -10));
	for (i = 0; i < 10; i++)
		printf("%c", string1[i]);
	printf ("\n");
	for (i = 0; i < 10; i++)
		printf("%c", string3[i]);
	printf("\ndifference: %d", strncmp(string1, string3, 100));
	printf("\n\n");

	printf("\n");
	j = -1;
	while (j < 20)
	{
		for (i = 0; i < 10; i++)
			{string1[i] = 'a' + i; string3[i] = 'a' + i;}
		string1[10] = 0;
		string3[10] = 0;
		for (i = 0; i < 5; i++)
			{string2[i] = '0' + i; string4[i] = '0' + i;}
		string2[5] = 0;
		string4[5] = 0;
//		printf("j = %d:\n", j);
		printf("%d:\n", j);
		printf("%zu, ", ft_strlcpy(string1, string2, j));
		printf("%zu\n", strlcpy(string3, string4, j));
		for (i = 0; i < 10; i++)
			printf("%c", string1[i]);
		printf ("\n");
		for (i = 0; i < 10; i++)
			printf("%c", string3[i]);
		printf("\ndifference: %d", strncmp(string1, string3, 100));
		printf("\n\n");
	j++;
	}
}
*/
