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

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
		f(lst->content);
		lst = lst->next;
	}
}
/*
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void	func01(void *c)
{
	char	*pc;

	pc = (char *)c;
	while (*pc++ != 0)
		*(pc - 1) = ft_toupper(*(pc - 1));
}

int	main(void)
{
	char 	n1[] = "this ";
	char	n2[] = "is a";
	char	n3[] = " test ";
	char	n4[] = "message!";
	char	n0[] = " haha";
	t_list	*start;
	t_list	*torel;
	t_list	**pdelcont;
	t_list	*runner;

	printf("1 start\n");
	start = ft_lstnew(n4);
	ft_lstadd_front(&start, ft_lstnew(n3));
	pdelcont = &(start->next); // nod n2 will be released later
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

	printf("\npart to upper:\n");
	runner = *pdelcont;
	while(runner != NULL)
	{
		printf("%s", (char *)runner->content);
		runner = runner->next;
	}

	printf("\n");
	ft_lstiter(*pdelcont, func01);

	printf("show modified, and to free the whole list:\n");
	while(start != NULL)
	{
		printf("%s", (char *)start->content);
		torel = start;
		start = start->next;
		if (torel->content != NULL)
			free(torel->content);
		free (torel);
	}
	printf("\n1 end\n");
	return (0);
}
*/
