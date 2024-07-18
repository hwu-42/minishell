/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 13:06:46 by hwu               #+#    #+#             */
/*   Updated: 2024/02/24 12:18:41 by hwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != 0 && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	else
		return (NULL);
}
/*
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	char	str[] = "afsfw56f4we54ff";
	int		c = 'a' + 256;

	printf("%d\n", (ft_strchr("abcdefg", 'g')!=NULL));
	printf("%c, %c, %c\n", c, (char)c, (unsigned char)c);
	printf("%c, %c, %c\n", str[0], (char)str[0], (unsigned char)str[0]);
	if ((ft_strchr(str, c) == strchr(str, c)) && (strchr(str,c)== NULL))
		printf("Not found!\n");
	else
		printf("ft_:\n%s\nori:\n%s\n", ft_strchr(str, c), strchr(str,c));

	return (0);
}
*/
