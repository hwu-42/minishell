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

char	*ft_itoa(int n)
{
	char	digit[100];
	int		i;
	char	*p;
	char	*s;

	i = 0;
	while (n != 0 || i == 0)
	{
		if (n % 10 >= 0)
			digit[i] = '0' + n % 10;
		else
			digit[i] = '0' - n % 10;
		i++;
		if (n < 0 && n > -10)
			digit[i++] = '-';
		n = n / 10;
	}
	p = malloc(i + 1);
	if (p == NULL)
		return (NULL);
	s = p;
	while (i > 0)
		*p++ = digit[i-- - 1];
	*p = 0;
	return (s);
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
	int		i = 0;
	char	*p;

	for(i=-11;i<19;i++)
	{
		p = ft_itoa(i);
		printf("%s\n", p);
		free(p);
	}
	i = INT_MAX;
	p = ft_itoa(i);
	printf("%s\n", p);
	free(p);
	i = INT_MIN;
	p = ft_itoa(i);
	printf("%s\n", p);
	free(p);
}
//i == 0 on line 22, make sure when n == 0, it also works
*/
