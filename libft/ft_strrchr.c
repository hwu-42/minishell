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

char	*ft_strrchr(const char *s, int c)
{
	size_t	len;

	len = ft_strlen(s);
	while (len != 0 && s[len] != (char)c)
		len--;
	if (s[len] == (char)c)
		return ((char *)(s + len));
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

	printf("%c, %c, %c\n", c, (char)c, (unsigned char)c);
	printf("%c, %c, %c\n", str[0], (char)str[0], (unsigned char)str[0]);
	if ((ft_strchr(str, c) == strrchr(str, c)) && (strrchr(str,c)== NULL))
		printf("Not found!\n");
	else
		printf("ft_:\n%s\nori:\n%s\n", ft_strrchr(str, c), strrchr(str,c));

	char	str1[] = "0";
	c = 'a';

	printf("ft_:\n%s\nori:\n%s\n", ft_strrchr(str1, c), strrchr(str1,c));

	c = 0;
	printf("ft_:\n%s\nori:\n%s\n", ft_strrchr(str1, c), strrchr(str1,c));
	printf("ft_:\n%p\nori:\n%p\n", ft_strrchr(str1, c), strrchr(str1,c));


	return (0);
}
*/
