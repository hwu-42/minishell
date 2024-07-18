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

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*pdest;
	const unsigned char	*psrc;
	size_t				i;

	pdest = dest;
	psrc = src;
	if (psrc > pdest)
	{
		i = 0;
		while (i < n)
		{
			pdest[i] = psrc[i];
			i++;
		}
	}
	else if (psrc < pdest)
	{
		while (n > 0)
		{
			pdest[n - 1] = psrc[n - 1];
			n--;
		}
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
	char	src1[]="0123456789abcdefghijklmnopqrstuvwxyz";
	char	src2[]="0123456789abcdefghijklmnopqrstuvwxyz";
	char	*dest1=src1+10;
	char	*dest2=src2+10;
	char	dest3[]="0123456789abcdefghijklmnopqrstuvwxyz";
	char	dest4[]="0123456789abcdefghijklmnopqrstuvwxyz";
	char	*src3=dest3+10;
	char	*src4=dest4+10;

//	unsigned int	i;
//	unsigned int	n;

	printf("src1:\n%s\n\n", src1);
	printf("src2:\n%s\n\n", src2);
	printf("src3:\n%s\n\n", src3);
	printf("src4:\n%s\n\n", src4);
	printf("dest1:\n%s\n\n", dest1);
	printf("dest2:\n%s\n\n", dest2);
	printf("dest3:\n%s\n\n", dest3);
	printf("dest4:\n%s\n\n", dest4);

	ft_memmove(dest1, src1, 20);
	memmove(dest2, src2, 20);
	ft_memmove(dest3, src3, 20);
	memmove(dest4, src4, 20);


	printf("after copy:\n");

	printf("dest1 by ft:\n%s\n\n", dest1);
	printf("dest2 by origin:\n%s\n\n", dest2);
	printf("dest3 by ft:\n%s\n\n", dest3);
	printf("dest4 by origin:\n%s\n\n", dest4);
}
*/
