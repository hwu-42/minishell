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

char	*ft_strdup(const char *src)
{
	size_t	len;
	size_t	i;
	char	*dup;

	len = ft_strlen(src);
	dup = malloc(len + 1);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < len +1)
	{
		dup[i] = src[i];
		i++;
	}
	return (dup);
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
	char	name[]="test.txt6u45\0jjjs";
	char	*dup, *dup2;

	dup = ft_strdup(name);
	dup2 = strdup(name);

	printf("if 2 lines are the same, it's right:\n");
	printf("%s\n%s\n", dup, dup2);
	free(dup);
	free(dup2);
}
*/
