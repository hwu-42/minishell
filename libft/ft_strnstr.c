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

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	blen;
	size_t	llen;

	if (big == NULL && len == 0)
		return (NULL);
	blen = ft_strlen(big);
	llen = ft_strlen(little);
	if (*little == 0)
		return ((char *)big);
	if (len == 0 || len < llen || *big == 0 || blen < llen)
		return (NULL);
	i = 0;
	while ((i < len - llen + 1) && (i < blen - llen + 1))
	{
		if (ft_strncmp(big + i, little, llen) == 0)
			break ;
		else
			i++;
	}
	if ((i < len - llen + 1) && (i < blen - llen) + 1)
		return ((char *)big + i);
	else
		return (NULL);
}
