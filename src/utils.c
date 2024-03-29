/******************************************************************************/
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgigot <mgigot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 14:54:46 by rheck             #+#    #+#             */
/*   Updated: 2024/02/13 11:40:28 by mgigot           ###   ########.fr       */
/*                                                                            */
/******************************************************************************/

#include "../inc/mini.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*tab;
	int		i;
	if (s1 == NULL)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	i = 0;
	tab = (char *)malloc(sizeof(char) * (len1 + len2 +1));
	if (!tab)
		return (NULL);
	while (*s1 != '\0')
	{
		tab[i++] = *s1;
		s1++;
	}
	while (*s2 != '\0')
	{
		tab[i++] = *s2;
		s2++;
	}
	tab[i] = '\0';
	return (tab);
}
size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	if (!str)
		return (0);
	while(str[i])
	{
		i++;
	}
	return(i);
}
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
}
void	ft_putendl_fd(char *s, int fd)
{
	ft_putstr_fd(s, fd);
	ft_putchar_fd('\n', fd);
}
char	**ft_arraydup(char **tab)
{
	char	**new_array;
	size_t	i;

	i = 0;
	while (tab[i] != NULL)
		i++;
	new_array = ft_calloc(sizeof(char *), i + 1);
	if (!new_array)
		return (NULL);
	i = 0;
	while (tab[i] != NULL)
	{
		new_array[i] = ft_strdup(tab[i]);
		if (new_array[i] == NULL)
		{
			free_arr(new_array);
			return (NULL);
		}
		i++;
	}
	return (new_array);
}

void	free_arr(char **split_arr)
{
	int	i;

	i = 0;
	while (split_arr[i])
	{
		free(split_arr[i]);
		i++;
	}
	free(split_arr);
}
char	*ft_strdup(const char *s)
{
	char	*new;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	new = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!new)
		return (NULL);
	while (s[i] != '\0')
	{
		new[i] = s[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
void	*ft_calloc(size_t count, size_t size)
{
	void	*data;
	size_t	ptr;

	ptr = count * size;
	if (count && ptr / count != size)
		return (NULL);
	data = malloc(count * size);
	if (data == 0)
		return (NULL);
	ft_bzero(data, size * count);
	return (data);
}
void	ft_bzero(void *s, size_t n)
{
	unsigned char	*p;

	p = s;
	while (n > 0)
	{
		*p = 0;
		n--;
		p++;
	}
}
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
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}