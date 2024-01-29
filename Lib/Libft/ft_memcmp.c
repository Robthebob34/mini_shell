/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgigot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:27:17 by mgigot            #+#    #+#             */
/*   Updated: 2023/04/14 11:37:03 by mgigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;
	int				x;

	i = 0;
	x = (int)n;
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (x == 0)
		return (0);
	while (x - 1 > 0)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
		x--;
	}
	return (str1[i] - str2[i]);
}
