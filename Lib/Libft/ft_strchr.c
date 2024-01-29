/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgigot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 12:20:21 by mgigot            #+#    #+#             */
/*   Updated: 2023/05/06 11:17:19 by mgigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	size_t	i;
	char	*ptr;
	char	cc;

	i = 0;
	cc = c;
	ptr = (char *)str;
	if(!str)
		return (0);
	while (ptr[i] != '\0')
	{
		if (ptr[i] == cc)
		{
			return (&ptr[i]);
		}
		i++;
	}
	if (cc == 0)
		return (&ptr[i]);
	return (0);
}
