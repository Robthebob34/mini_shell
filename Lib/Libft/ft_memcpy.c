/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgigot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 15:07:04 by mgigot            #+#    #+#             */
/*   Updated: 2023/04/10 14:43:49 by mgigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t num)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	i = 0;
	if (!s && !d)
		return (0);
	while (num > 0)
	{
		d[i] = s[i];
		i++;
		num--;
	}
	return (dest);
}
