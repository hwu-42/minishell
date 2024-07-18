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

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	char	*p;
	size_t	i;

	len = 0;
	while (s[len])
		len++;
	p = malloc(len + 1);
	if (p == NULL)
		return (NULL);
	i = 0;
	while (i++ < len)
		p[i - 1] = f(i - 1, s[i - 1]);
	p[i - 1] = 0;
	return (p);
}
/*


static char	func(unsigned int n, char c)
{
	return (n + c);
}

static char	upper(unsigned int n, char c)
{
	if (n > 10)
		return (c + 'A' - 'a');
	else
		return ('x');
}

#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>


int	main(void)
{
	char	name[]="  ";
	char	name2[]="                                     ";
	char	name3[]="abcdefghijklmnopqrstuvwxyz";
	char	*p;

	p = ft_strmapi(name, func);
	if (p != NULL)
	printf("%s\n", p);
	if (p != NULL)
		free(p);

	p = ft_strmapi(name2, func);
	if (p != NULL)
	printf("%s\n", p);
	if (p != NULL)
		free(p);

	p = ft_strmapi(name3, upper);
	if (p != NULL)
	printf("%s\n", p);
	if (p != NULL)
		free(p);
	return (0);
}
*/
