/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 19:28:55 by hwu               #+#    #+#             */
/*   Updated: 2023/12/12 14:37:07 by hwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
static int	mypower(int a, int b)
{
	int	result;

	result = 1;
	while (b > 0)
	{
		result *= a;
		b--;
	}
	return (result);
}

static int	aton(const char *str)
{
	int	i;
	int	j;
	int	res;

	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	j = 0;
	res = 0;
	while (j < i)
	{
		res += mypower(10, (i - j -1)) * (str[j] - '0');
		j++;
	}
	return (res);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;
	int	i;

	while ((*str > 8 && *str < 14) || *str == ' ')
		str++;
	if (!(*str == '+' || *str == '-' || (*str >= '0' && *str <= '9')))
		return (0);
	sign = 1;
	i = 0;
	if (*str == '+' || *str == '-')
	{
		sign -= 2 * (*str == '-');
		i++;
	}
	if (!(str[i] >= '0' && str[i] <= '9'))
		return (0);
	result = sign * aton(str + i);
	return (result);
}
/*
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int	main(int argc, char *argv[])
{
	char *s[] = {"   -++--2147483648.sfgf",
	"a42", "\x09+1", "-12a", "++100a", "+-1",
	"--1", "+0", "-0", "0", "1", "245-", "-2147483648", "-2147483649",
	"2147483648", "2147483647", "-1sfs555", "1",
	"111111111111111111", "00001", "0000a", ""};
	char *t[] = {"0", "0", "1", "-12", "0", "0", "0", "0", "0", "0",
	"1", "245", "-2147483648", "2147483647", "-2147483648",
	 "2147483647", "-1", "1", "-2074054201", "1", "0", ""};

	int	i=0;
	int isOK=1;

	if (argc >= 2)
		printf("result is:\n%d", ft_atoi(argv[1]));
	printf("input\nexpected result\nft result\n ori result\n\n");
	while (*s[i] != 0)
	{
		printf("%s:\n", s[i]);
		printf("%s:\n", t[i]);
		printf("%d\n", ft_atoi(s[i]));
		printf("%d\n", atoi(s[i]));
		printf("right? %d\n\n", ft_atoi(s[i]) == atoi(s[i]));
		if (ft_atoi(s[i]) != atoi(s[i]))
			isOK = 0;
		i++;
		printf("\n\n");
	}
	printf("isOK is %d\n", isOK);
}
*/
