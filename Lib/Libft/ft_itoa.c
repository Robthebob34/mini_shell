/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgigot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 10:26:14 by mgigot            #+#    #+#             */
/*   Updated: 2023/05/01 15:22:54 by mgigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	*placezero(char *str, int n)
{
	str[0] = '0';
	str[n] = '\0';
	return (str);
}

static char	*checkstrsign(char *str, int n)
{
	if (str[0] != '-')
		str[0] = "0123456789"[n % 10];
	return (str);
}

static int	countdivision(int x)
{
	size_t	count;

	count = 0;
	if (x == 0)
		count++;
	if (x < 0)
		count++;
	while (x != 0)
	{
		x = x / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	size_t			x;
	unsigned int	newn;
	char			*str;

	newn = (unsigned int)n;
	x = countdivision(newn);
	str = malloc(sizeof(char) * x + 1);
	if (!str)
		return (NULL);
	str = placezero(str, x);
	if (n < 0)
	{	
		newn = -n;
		str[0] = '-';
	}
	if (x == 1)
		str[x -1] = "0123456789"[newn % 10];
	while (x - 1 != 0)
	{
		str[x - 1] = "0123456789"[newn % 10];
		newn = newn / 10;
		x--;
	}
	str = checkstrsign(str, newn);
	return (str);
}
