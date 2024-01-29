/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgigot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:42:35 by mgigot            #+#    #+#             */
/*   Updated: 2023/04/14 12:17:29 by mgigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strnstr(const char *main, const char *second, size_t len)
{
	size_t	i;
	size_t	y;
	char	*result;

	i = 0;
	y = 0;
	result = (char *)main;
	if (second[i] == 0)
		return (result);
	while (result[i] != '\0' && len > 0)
	{
		if (result[i] == second[y] && len >= ft_strlen(second))
		{
			while ((result[i + y] == second[y]
					&& result[i + y] != '\0' && second[y] != '\0'))
				y++;
			if (second[y] == '\0')
				return (result + i);
			y = 0;
		}
		i++;
		len--;
	}
	return (0);
}
