/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgigot <mgigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 12:29:21 by mgigot            #+#    #+#             */
/*   Updated: 2023/04/19 12:30:53 by mgigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*new;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_calloc(1, 1));
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	new = malloc(sizeof(char) * (len + 1));
	if (!new)
		return (0);
	ft_strlcpy(new, s + start, len + 1);
	return (new);
}
