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

static int	in(char a, const char *set)
{
	while (*set != a && *set != 0)
	{
		set++;
	}
	if (*set == a)
	{
		return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;
	size_t			len;
	char			*sub;

	start = 0;
	end = ft_strlen(s1);
	while ((in(s1[start], set) == 1) && (s1[start] != 0))
		start++;
	if (s1[start] == 0)
	{
		sub = malloc(1);
		if (sub != NULL)
			*sub = 0;
		return (sub);
	}
	while (in(s1[end], set) && end > start)
		end--;
	len = end - start + 1;
	return (ft_substr(s1, start, len));
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
	char	name[]="_.---a2\t1...\0abcdefg12.-345.---\0jjjs.k.-";
	char	set[] = ".- _";
	char	*clean;

	clean = ft_strtrim(name, set);
	printf("%s\n", clean);
	free(clean);
}
*/
