/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgigot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 12:28:53 by mgigot            #+#    #+#             */
/*   Updated: 2023/04/12 10:47:30 by mgigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	size_t	len;
	int		end;
	char	*trimmed;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	len = ft_strlen(s1);
	end = len - 1;
	while (s1[start] != '\0' && ft_strchr(set, s1[start]) != 0)
		start++;
	while (end > start && ft_strchr(set, s1[end]) != 0)
		end--;
	trimmed = malloc(sizeof (char) * (end - start + 2));
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, s1 + start, end - start + 2);
	trimmed[end - start + 1] = '\0';
	return (trimmed);
}
