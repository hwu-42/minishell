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

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*pt;
	t_list	*last;

	new = NULL;
	if (lst == NULL)
		return (new);
	while (lst != NULL)
	{
		pt = malloc(sizeof(t_list));
		if (pt == NULL)
			return (ft_lstclear(&new, del), NULL);
		if (new == NULL)
			new = pt;
		if (new == pt)
			last = pt;
		pt->content = f(lst->content);
		if (pt->content == NULL)
			return (ft_lstclear(&new, del), NULL);
		last->next = pt;
		last = last->next;
		pt->next = NULL;
		lst = lst->next;
	}
	return (new);
}
/*
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	ft_freecontent(void *pt)
{
	free (((t_list *)pt)->content);
	((t_list *)pt)->content = NULL;
}

void	*func04(void *c)
{
	char	*newc;
	char	*p;
	char	*pc;

	newc = malloc(ft_strlen(c) + 1);
	if (newc == NULL)
		return (NULL);
	p = newc;
	pc = c;
	while (*pc != 0)
	{
		if (*pc <= 'z' && *pc >= 'a')
			*p = *pc + 'A' - 'a';
		else
			*p = *pc;
		p++;
		pc++;
	}
	*p = 0;
	return (newc);
}

int	main(void)
{
	char 	n1[] = "this ";
	char	n2[] = "is a";
	char	n3[] = " test ";
	char	n4[] = "message!";
	char	n0[] = " haha~!";
	t_list	*start;
	t_list	*torel;
	t_list	*new;
	t_list	*runner;

	printf("main start:\n");

	start = ft_lstnew(n4);
	ft_lstadd_front(&start, ft_lstnew(n3));
	ft_lstadd_front(&start, ft_lstnew(n2));
	ft_lstadd_front(&start, ft_lstnew(n1));
	ft_lstadd_back(&start, ft_lstnew(n0));

	printf("list created:\n");
	runner = start;
	while(runner != NULL)
	{
		printf("%s", (char *)runner->content);
		runner = runner->next;
	}
	printf("\n");

	new = ft_lstmap(start, func04, ft_freecontent);
	if (new == NULL)
		printf("\nnew list failed\n");
	printf("new list address: %p", new);
	printf("\nnew list created:\n");
	runner = new;
	while(runner != NULL)
	{
		printf("%s", (char *)runner->content);
		runner = runner->next;
	}

	printf("\nfree the old list:\n");
	while(start != NULL)
	{
		printf("%s", (char *)start->content);
		torel = start;
		start = start->next;
		if (torel->content != NULL)
			free(torel->content);
		free (torel);
	}

	printf("\nfree the new list:\n");
	start = new;
	while(start != NULL)
	{
		printf("%s", (char *)start->content);
		torel = start;
		start = start->next;
		if (torel->content != NULL)
			free(torel->content);
		free (torel);
	}

	printf("\nmain end!\n");
	return (0);
}
*/
