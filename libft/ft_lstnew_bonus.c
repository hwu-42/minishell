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

t_list	*ft_lstnew(void *content)
{
	t_list	*pt;

	pt = malloc(sizeof(t_list));
	if (pt == NULL)
		return (NULL);
	pt->content = content;
	pt->next = NULL;
	return (pt);
}
/*
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	char 	name[] = "this is a test message!";
	t_list	t;

	t.next = ft_lstnew(name);
	printf("%s\n", (char *)t.next->content);
	free (t.next);
	printf("done!\n");
	return (0);
}
*/
