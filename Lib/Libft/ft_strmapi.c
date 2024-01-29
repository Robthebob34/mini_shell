/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgigot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 12:09:25 by mgigot            #+#    #+#             */
/*   Updated: 2023/04/13 12:42:37 by mgigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	int		i;
	char	*result;

	if (!s || !f)
		return (NULL);
	len = ft_strlen(s);
	i = 0;
	result = malloc(len + 1);
	if (!result)
		return (NULL);
	while (len > 0)
	{
		result[i] = f(i, s[i]);
		i++;
		len--;
	}
	result[i] = '\0';
	return (result);
}
