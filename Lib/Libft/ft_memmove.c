/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgigot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 11:24:23 by mgigot            #+#    #+#             */
/*   Updated: 2023/04/13 13:56:57 by mgigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*d;
	unsigned char	*s;

	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	if (dest == src)
		return (dest);
	while (i < n)
	{
		if (dest > src)
		{
			d[n - 1] = s[n - 1];
			n--;
		}
		else
		{
			d[i] = s[i];
			i++;
		}	
	}
	return (dest);
}
