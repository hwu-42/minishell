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

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
/*
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	char 	n1[] = "this ";
	char	n2[] = "is a";
	char	n3[] = " test ";
	char	n4[] = "message!";
	t_list	*start;
	t_list	*torel;

	start = ft_lstnew(n4);
	ft_lstadd_front(&start, ft_lstnew(n3));
	ft_lstadd_front(&start, ft_lstnew(n2));
	ft_lstadd_front(&start, ft_lstnew(n1));
	while(start != NULL)
	{
		printf("%s", (char *)start->content);
		torel = start;
		start = start->next;
		if (torel->content != NULL)
			free(torel->content);
		free (torel);
	}
	return (0);
}
*/
