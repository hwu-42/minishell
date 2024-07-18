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

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	del(lst->content);
	free(lst);
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

int	main(void)
{
	char 	n1[] = "this ";
	char	n2[] = "is a";
	char	n3[] = " test ";
	char	n4[] = "message!";
	char	n0[] = " haha";
	t_list	*start;
	t_list	*torel;
	t_list	*pdelcont;
	t_list	*runner;

	printf("1 start\n");
	start = ft_lstnew(n4);
	ft_lstadd_front(&start, ft_lstnew(n3));
	ft_lstadd_front(&start, ft_lstnew(n2));
	pdelcont = start; // nod n2 will be released later
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
	ft_lstdelone(pdelcont, ft_freecontent);

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
