/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 15:27:43 by hwu               #+#    #+#             */
/*   Updated: 2023/11/29 15:46:22 by hwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static size_t	ft_strlcat2(char *dest, const char *src, size_t nb)
{
	size_t	dlen;
	size_t	slen;
	size_t	left;

	dlen = ft_strlen(dest);
	slen = ft_strlen(src);
	left = nb - dlen - 1;
	{
		while (*dest != 0)
			dest++;
		while (*src != 0 && left > 0)
		{
			*dest++ = *src++;
			left--;
		}
		*dest = 0;
	}
	if (nb < dlen)
		return (nb + slen);
	else
		return (dlen + slen);
}

size_t	ft_strlcat(char *dest, const char *src, size_t nb)
{
	size_t	dlen;
	size_t	slen;

	if (dest == NULL && nb == 0)
		return (0);
	dlen = ft_strlen(dest);
	slen = ft_strlen(src);
	if (dest == NULL)
		return (0);
	if (src == NULL)
		return (dlen);
	if (nb < dlen + 1)
		return (nb + slen);
	return (ft_strlcat2(dest, src, nb));
}
/*
size_t	ft_strlcat(char *dest, const char *src, size_t nb)
{
	size_t	dlen;
	size_t	slen;
	size_t	left;

	dlen = ft_strlen(dest);
	slen = ft_strlen(src);
	if (nb < dlen + 1)
		return (nb + slen);
	left = nb - dlen - 1;
	{
		while (*dest != 0)
			dest++;
		while (*src != 0 && left > 0)
		{
			*dest++ = *src++;
			left--;
		}
		*dest = 0;
	}
	if (nb < dlen)
		return (nb + slen);
	else
		return (dlen + slen);
}
*/
/*
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <bsd/string.h>

int	main(void)
{
	char	src[] = "copied part";
	char	dest[50] = "old part 123456789";
	char	dest2[50] = "";
	char	dest1[50] = "";
	size_t	m, n;
	int	j;

	for(j=-2; j< 50; j++)
	{
		printf("test %d:\n", j);
		strlcpy(dest1, dest, 50);
		strlcpy(dest2, dest, 50);
		m = strlcat(dest1, src, j);
		n = ft_strlcat(dest2, src, j);
		printf("result compare:\n");
		printf("%s\n%s\n", dest1, dest2);
		printf("return compare:\n");
		printf("%zu\n%zu\n", m, n);
	}
	return 0;
}
*/
