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

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*pt;

	pt = ft_lstlast(*lst);
	if (pt == NULL)
		*lst = new;
	else
		pt->next = new;
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
	char	n0[] = " haha";
	t_list	*start;
	t_list	*torel;

	start = NULL;
//	start = ft_lstnew(n4);
//	ft_lstadd_front(&start, ft_lstnew(n3));
//	ft_lstadd_front(&start, ft_lstnew(n2));
//	ft_lstadd_front(&start, ft_lstnew(n1));
	ft_lstadd_back(&start, ft_lstnew(n0));
	ft_lstadd_back(&start, ft_lstnew(n1));
	ft_lstadd_back(&start, ft_lstnew(n2));
	ft_lstadd_back(&start, ft_lstnew(n3));
	ft_lstadd_back(&start, ft_lstnew(n4));
	while(start != NULL)
	{
		printf("%s", (char *)start->content);
		torel = start;
		start = start->next;
		free (torel);
	}
	printf("\n");
	start = NULL;
	ft_lstadd_back(&start, ft_lstnew(n0));
	while(start != NULL)
	{
		printf("%s", (char *)start->content);
		torel = start;
		start = start->next;
		free (torel);
	}
	return (0);
}
*/
