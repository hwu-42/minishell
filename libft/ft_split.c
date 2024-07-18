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

static int	size_unit(char const *s, char c, size_t *punit)
{
	*punit = 0;
	if (s == NULL)
		return (0);
	while (*s != 0)
	{
		while (*s == c)
			s++;
		if (*s != 0)
			(*punit)++;
		while (*s != c && *s != 0)
			s++;
	}
	return (1);
}

static char	*load(char const *s, int size)
{
	char	*p;
	int		j;

	p = malloc(size + 1);
	if (p == NULL)
		return (NULL);
	p[size] = 0;
	j = 0;
	while (j < size)
	{
		p[j] = *(s - size + j);
		j++;
	}
	return (p);
}

static char	**pre(char const *s, char c, size_t *punit)
{
	char	**p;

	size_unit(s, c, punit);
	p = (char **)malloc(sizeof(char *) * (*punit + 1));
	if (p == NULL)
		return (NULL);
	p[*punit] = NULL;
	return (p);
}

char	**ft_split(char const *s, char c)
{
	size_t		unit;
	char		**p;
	int			i;
	int			size;

	p = pre(s, c, &unit);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (*s != 0)
	{
		while (*s == c)
			s++;
		size = 0;
		while (*s != c && *s != 0)
		{
			size++;
			s++;
		}
		if (size == 0)
			break ;
		p[i++] = load(s, size);
	}
	return (p);
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
	char	*name[] = {"44 4", "  this is right", "  this is right   ",
	"   ", "\0 ", "", "end"};
	char	c = ' ';
	char	**p;
	char	**p1;
	int		i = 0;

	while (ft_strncmp(name[i], "end", 5) != 0)
	{
		p = ft_split(name[i], c);
		p1 = p;
		while (*p != NULL)
		{
			printf("%s ", *p);
			free (*p);
			p++;
		}
		free (p1);
		i++;
		printf("\n\n");
	}
	printf("\ndone!");
}
*/
