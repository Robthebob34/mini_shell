/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgigot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 14:31:22 by mgigot            #+#    #+#             */
/*   Updated: 2023/04/08 13:11:51 by mgigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	size_t			i;
	unsigned int	j;
	unsigned char	*ptr;

	ptr = (unsigned char *)str;
	j = (unsigned char)c;
	i = 0;
	while (n > 0)
	{
		if (ptr[i] == j)
			return (&ptr[i]);
		i++;
		n--;
	}
	return (0);
}
