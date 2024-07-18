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

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*pdest;
	const char	*psrc;

	if (src == NULL && dest == NULL)
		return (NULL);
	pdest = dest;
	psrc = src;
	while (n > 0)
	{
		pdest[n - 1] = psrc[n - 1];
		n--;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	char	src[]="jafof23fjsf9823fhsaséfg2";
	char	dest1[100]="";
	char	dest2[100]="";
	unsigned int	i;

	printf("src:\n%s\n\n", src);

	printf("dest1 before operation:\n");
	for (i=0;i<100;i++)
	{
		printf("%c", dest1[i]);
	}

	printf("\ndest2 before operation:\n");
	for (i=0;i<100;i++)
	{
		printf("%c", dest2[i]);
	}
	printf("\n");

	ft_memcpy(dest1, src, 12);
	memcpy(dest2, src, 12);
	printf("12 charactors copied\n");

	printf("dest1 after copy by ft_memcpy:\n");
	for (i=0;i<100;i++)
	{
		printf("%c", dest1[i]);
	}
	printf("\n");

	printf("\ndest2 after copy by memcpy:\n");
	for (i=0;i<100;i++)
	{
		printf("%c", dest2[i]);
	}
}
*/
