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

void	*ft_bzero(void *s, size_t n)
{
	char	*str;
	size_t	i;

	str = s;
	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
	return (s);
}
/*
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	char	buffer1[]="jafof23fjsf9823fhsaséfg2";
	char	buffer2[]="jafof23fjsf9823fhsaséfg2";
	unsigned int	i;

	printf("%s\n", buffer1);
	bzero(buffer1, 3);
	for (i=0;i<sizeof(buffer1);i++)
	{
		printf("%c", buffer1[i]);
	}
	printf("\n");
	printf("compare with bzero:\n");
	printf("%s\n", buffer2);
	ft_bzero(buffer2, 3);
	for (i=0;i<sizeof(buffer1);i++)
	{
		printf("%c", buffer2[i]);
	}
}
*/
