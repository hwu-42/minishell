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

static size_t	maxnum(void)
{
	size_t	num;
	size_t	i;

	i = 0;
	num = 0;
	while (i < sizeof(size_t) * 8)
	{
		num = num << 1 | 1;
		i++;
	}
	return (num);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;

	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if ((maxnum() / nmemb) < size)
		return (NULL);
	else
	{
		p = malloc(nmemb * size);
		if (p == NULL)
			return (NULL);
		ft_bzero(p, nmemb * size);
		return (p);
	}
}
/*
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <stddef.h>
#include <malloc.h>
#define num_a 111
#define num_b 10
int	main(void)
{
	void	*p;
	void	*pp;
	void	*ppp;

	printf("the size of memory allcated by ft_calloc, calloc, malloc:\n");
	p = ft_calloc(num_a, num_b);
	pp = calloc(num_a, num_b);
	ppp = malloc(num_a * num_b);
	if (p == NULL)
		printf("allocation fail");
	else
		printf("%zu\n", malloc_usable_size(p));
	printf("%zu\n", malloc_usable_size(pp));
	printf("%zu\n", malloc_usable_size(ppp));
	free(p);
	free(pp);
	free(ppp);
	return (0);
}
*/
