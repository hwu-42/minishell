/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:05:37 by hwu               #+#    #+#             */
/*   Updated: 2024/02/24 11:52:56 by hwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	j;

	if (n < 1)
		return (0);
	i = 1;
	j = 0;
	while ((s1[j] != 0) && (s2[j] != 0) && (i < n))
	{
		if (((unsigned char)s1[j] != (unsigned char)s2[j]))
			break ;
		j++;
		i++;
	}
	if ((unsigned char)s1[j] == (unsigned char)s2[j])
		return (0);
	else if ((unsigned char)s1[j] > (unsigned char)s2[j])
		return (1);
	else
		return (-1);
}
/*
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	int	i;
	char c[]="";
	char d[]="1";
	char e[]="1";
	char f[]="";

	printf("if the numbers are the same on each line, then it's right:\n");
	for (i = 0; i < 10; i++)
		printf("%d, %d\n", strncmp(c, d, i), ft_strncmp(c, d, i));
	printf("test case 2:\n");
	for (i = 0; i < 10; i++)
		printf("%d, %d\n", strncmp(e, f, i), ft_strncmp(e, f, i));

	return (0);
}
*/
