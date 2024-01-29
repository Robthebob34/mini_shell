/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgigot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 13:34:46 by mgigot            #+#    #+#             */
/*   Updated: 2023/04/13 13:01:30 by mgigot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static char	**freearray(char **str, size_t index)
{
	size_t	i;

	i = 0;
	while (i < index)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

static int	checknbline(const char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && (str[i + 1] == c || !str[i + 1]))
			count++;
		i++;
	}
	return (count + 1);
}

static char	*cpy(const char *str, int end, char c)
{
	size_t	i;
	int		start;
	char	*cpy;

	i = 0;
	start = end;
	if (start == 0)
		end = end + 1;
	while (start != 0 && str[start - 1] != c)
		start--;
	cpy = malloc(sizeof(char) * ((end - start) + 1));
	if (!cpy)
		return (NULL);
	while (end > start)
	{
		if (str[start] != c)
		{
			cpy[i] = str[start];
			i++;
		}
		start++;
	}
	cpy[i] = '\0';
	return (cpy);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	int		i;
	size_t	y;
	size_t	x;

	i = -1;
	y = 0;
	if (!s)
		return (NULL);
	x = checknbline(s, c);
	new = malloc(sizeof(char *) * (x));
	if (!new)
		return (NULL);
	while (s[++i] != '\0')
	{
		if ((s[i] != c && s[i + 1] == c) || (s[i] != c && s[i + 1] == '\0'))
		{
			new[y] = cpy(s, i + 1, c);
			if (!new[y])
				return (freearray(new, y));
			y++;
		}
	}
	new[y] = 0;
	return (new);
}
