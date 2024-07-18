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

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;

	i = 0;
	while (*s != 0)
		f(i++, s++);
}
/*
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

static void	func3(unsigned int n, char *c)
{
	*c = *c + n;
}

static void	upper2(unsigned int n, char *c)
{
	if (n > 10)
		*c = *c + 'A' - 'a';
}

int	main(void)
{
	char	name[]="  ";
	char	name2[]="                                     ";
	char	name3[]="abcdefghijklmnopqrstuvwxyz";

	ft_striteri(name, func3);
	printf("%s\n", name);

	ft_striteri(name2, func3);
	printf("%s\n", name2);

	ft_striteri(name3, upper2);
	printf("%s\n", name3);

	return (0);
}
*/
