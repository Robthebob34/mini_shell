#include <../../inc/mini.h>
void	*ft_free(char **p1, char **p2)
{
	if (p1 && *p1 != NULL)
	{
		free(*p1);
		*p1 = NULL;
	}
	if (p2 && *p2 != NULL)
	{
		free(*p2);
		*p2 = NULL;
	}
	return (NULL);
}

char	*get__line(char **buffer)
{
	char	*line;
	char	*tmp;
	size_t	i;

	if (!*buffer || !**buffer)
		return (ft_free(buffer, NULL));
	i = 0;
	while ((*buffer)[i] != '\n' && (*buffer)[i] != '\0')
		i++;
	if ((*buffer)[i] != '\0')
		i++;
	tmp = *buffer;
	line = ft_substr(*buffer, 0, i);
	if (!line)
		return (ft_free(buffer, NULL));
	*buffer = ft_substr(*buffer, i, ft_strlen(*buffer + i));
	if (!*buffer)
		return (ft_free(&tmp, &line));
	ft_free(&tmp, NULL);
	return (line);
}

char	*get_join(char *s1, char *s2)
{
	char	*str;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1)
		len_s1 = 0;
	else
		len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	str = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!str)
		return (ft_free(&s1, &s2));
	ft_memcpy(str, s1, len_s1);
	ft_memcpy(str + len_s1, s2, len_s2);
	str[len_s2 + len_s1] = '\0';
	ft_free(&s1, NULL);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*buff_read;
	int			byte_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	byte_read = 1;
	buff_read = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff_read)
		return (ft_free(&buffer, NULL));
	while (!ft_strchr(buffer, '\n') && byte_read > 0)
	{
		byte_read = read(fd, buff_read, BUFFER_SIZE);
		if (byte_read == -1)
			return (ft_free(&buffer, &buff_read));
		if (byte_read > 0)
		{
			buff_read[byte_read] = '\0';
			buffer = get_join(buffer, buff_read);
			if (!buffer)
				return (NULL);
		}
	}
	free(buff_read);
	return (get__line(&buffer));
}