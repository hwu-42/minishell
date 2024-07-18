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

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	if (start > ft_strlen(s) -1)
	{
		sub = malloc(1);
		if (sub != NULL)
			*sub = 0;
		return (sub);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	sub = malloc(len + 1);
	if (sub == NULL)
		return (sub);
	i = 0;
	while (i < len && s[start + i] != 0)
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = 0;
	return (sub);
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
	char	name[]="0123456789\0jjjs";
	char	*sub;
	int	i;
	size_t j;

	for (j=0;j<ft_strlen(name)+2;j++)
	{
		for (i=0; i<15; i++)
		{
			printf("len = %zu, start = %zu, len = %d:\n", ft_strlen(name), j, i);
			sub = ft_substr(name, j, i);
			if (sub == NULL)
				printf("sub is NULL\n");
			else
			{
				printf("%s\n", sub);
				free(sub);
			}
		}
	}
}
*/
