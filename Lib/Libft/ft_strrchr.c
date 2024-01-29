/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgigot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 13:11:10 by mgigot            #+#    #+#             */
/*   Updated: 2023/04/14 14:13:09 by mgigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*ptr;

	i = 0;
	ptr = (char *)str;
	while (ptr[i] != '\0')
		i++;
	while (i >= 0)
	{	
		if (ptr[i] == (char)c)
			return (&ptr[i]);
		else
			i--;
	}
	return (NULL);
}
