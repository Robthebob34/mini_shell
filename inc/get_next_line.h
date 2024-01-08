#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
size_t	ft_strlen(const char *str);
char	*get_join(char *s1, char *s2);
char	*get__line(char **buffer);
void	*ft_free(char **p1, char **p2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*ft_memcpy(void *dest, const void *src, size_t num);
char	*ft_strchr(const char *str, int c);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

#endif